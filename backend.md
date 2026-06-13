# Backend

* Firebase handles identity, mobile client session security, and out-of-the-box user auth.

* MySQL manages your relational business logic (users, organizations, device metadata, hardware profiles, billing).

* InfluxDB acts as your high-performance time-series engine, swallowing raw historical telemetry streams without sweating or racking up massive bills.

Since you are bridging a mobile application ecosystem (Firebase) with a traditional relational and time-series backend, you need a smart data flow to tie them together cleanly.

## The Recommended Architecture

To make this work seamlessly, your mobile app shouldn't talk directly to MySQL or InfluxDB. Instead, you'll want an intermediate API layer (like a Node.js, Python, or Go backend) or leverage a lightweight ingestion engine.

### 1. The Authentication & Access Link
When a user logs into your mobile app via Firebase Auth, Firebase generates a JWT (JSON Web Token).
* Your app sends this JWT in the Authorization header of every HTTP/gRPC request to your central backend.

* Your backend verifies the token using the Firebase Admin SDK.

* Once verified, your backend maps that Firebase uid to your relational data in MySQL to check permissions (e.g., "Does this user own the asset containing this sensor?").

### 2. Splitting the Data Mode
To keep things clean, divide your data models explicitly across the two databases:

#### MySQL (The Operational Brain)
Keep this structured, relational, and highly indexed for business logic.
* users (id, firebase_uid, email, company_id, created_at)
* devices (id, mac_address, hardware_type, firmware_version, installation_date, status)
* gateways_or_networks (provisions, routing keys, or regional parameters like AS923/AU915 profiles if applicable)
* device_assignments (mapping which device belongs to which customer or site)

#### InfluxDB (The Historical Stream)
Keep this strictly for append-only timestamped telemetry data. Use tags for metadata you intend to filter by, and fields for the actual values.
* **Measurement:** sensor_telemetry
* **Tags (Indexed):** device_id, hardware_type
* **Fields (Unindexed values):** temperature, humidity, battery_voltage, rssi

**Critical Implementation Tips for This Stack**
##### 1. InfluxDB Writing Strategy
Do not let your devices write to InfluxDB using an entirely separate pipeline from your business logic if you need real-time validation.
* **Option A (Centralized):** Devices send data to your backend API (or MQTT broker/Node-RED pipeline). The backend checks MySQL to ensure the device is active, logs the payload to InfluxDB, and can optionally push a "current status" broadcast if needed.

* **Option B (Direct Influx Write):** If devices write directly to InfluxDB using tokens, make sure you use InfluxDB's bucket-level permissions to isolate data traffic, though a centralized gateway API is usually safer for device validation.

##### 2. Handling Timezones and Aggregations
One of the best reasons you chose InfluxDB is Flux/SQL querying for historical metrics. Instead of pulling 10,000 raw rows to your mobile app to draw a 30-day chart, use InfluxDB's windowing functions to downsample the data server-side:
``` SQL
-- Example concept: Downsampling raw data to 1-hour averages for the app chart
SELECT MEAN("temperature") 
FROM "sensor_telemetry" 
WHERE "device_id" = 'dev_123' AND time > now() - 30d 
GROUP BY time(1h)
```

##### 3. The Firebase Sync
If your app needs real-time updates (like a live dashboard showing a toggle switch state changing instantly), you can occasionally dual-write just the latest packet to Firestore or Firebase Realtime Database. However, if your app can tolerate pulling the "latest status" via a quick API call to InfluxDB/MySQL on dashboard load, you can keep Firebase strictly limited to Authentication, keeping your client side incredibly lightweight.
