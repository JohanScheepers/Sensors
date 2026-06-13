# FMC Rules Trigger

o handle alerting for sensors with multiple data streams (like a device that monitors temperature, humidity, and battery voltage simultaneously), you need to separate what the sensor is reporting from what rules trigger an alert.

Since you are using MySQL for business logic and relational structures, you should store your alert thresholds, rules, and configurations right there. InfluxDB will store the raw data, but MySQL will act as the "brain" that evaluates if a threshold has been crossed.

Here is the cleanest production database schema design for an IoT alert system, along with how it functions when a multi-sensor payload arrives.

## 1. The MySQL Database Schema

You need a relational structure that links a physical device to its specific data channels (metrics) and defines the alert rules for those channels.

**The `sensor_metrics` Table**
This defines the individual streams of data a device can send. A single physical device can have multiple rows here.
```SQL
CREATE TABLE sensor_metrics (
    id INT AUTO_INCREMENT PRIMARY KEY,
    device_id VARCHAR(100) NOT NULL, -- Links to your main devices table
    metric_name VARCHAR(50) NOT NULL, -- e.g., 'temperature', 'humidity', 'voltage'
    unit VARCHAR(10),                -- e.g., 'C', '%', 'V'
    UNIQUE KEY dev_metric (device_id, metric_name)
);
```
The `alert_configs` Table
This is where you store the actual rules. By referencing the sensor_metrics table, you can set a rule specifically for "temperature" without affecting "humidity."
```SQL
CREATE TABLE alert_configs (
    id INT AUTO_INCREMENT PRIMARY KEY,
    metric_id INT NOT NULL,
    rule_name VARCHAR(100) NOT NULL,   -- e.g., 'High Temp Warning'
    condition_type VARCHAR(10) NOT NULL, -- '>', '<', '=', '!='
    threshold_value DOUBLE NOT NULL,     -- The numeric value to trigger on (e.g., 45.0)
    cooldown_minutes INT DEFAULT 30,     -- Prevents spamming notifications
    is_enabled BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (metric_id) REFERENCES sensor_metrics(id) ON DELETE CASCADE
);
```

** The `alert_state_tracker` Table**
To prevent flooding a user's phone with notifications every 10 seconds while a sensor is in an error state, you need a table to track the current state of an alert and when a notification was last sent.
```SQL
CREATE TABLE alert_state_tracker (
    config_id INT PRIMARY KEY,
    is_currently_triggered BOOLEAN DEFAULT FALSE,
    last_notified_at TIMESTAMP NULL,
    FOREIGN KEY (config_id) REFERENCES alert_configs(id) ON DELETE CASCADE
);
```

## 2. How the System Evaluates a Multi-Reading Payload

When a multi-sensor packet hits your central backend pipeline (e.g., via an API or MQTT ingestion step), your code evaluates the rules using a simple three-step processing loop.

**Step A: The Payload Arrives**
Your device sends a single JSON packet containing all its current readings:
```JSON
{
  "device_id": "sensor_node_99",
  "temperature": 46.5,
  "humidity": 32.1,
  "voltage": 3.6
}
```
**Step B: The Database Lookup & Match**
Your backend queries MySQL to get all the active alert rules configured for this specific device id
```SQL
SELECT 
    m.metric_name, 
    c.id AS config_id, c.condition_type, c.threshold_value, c.cooldown_minutes,
    t.is_currently_triggered, t.last_notified_at
FROM sensor_metrics m
JOIN alert_configs c ON m.id = c.metric_id
LEFT JOIN alert_state_tracker t ON c.id = t.config_id
WHERE m.device_id = 'sensor_node_99' AND c.is_enabled = TRUE;
```
**Step C: Evaluating the Logic Loop**
Your backend loops through the results of that query and compares them directly against the values in the incoming payload:
1. Evaluate Temperature ($46.5^\circ\text{C}$):
    * The rule says: Trigger if temperature > 45.0.
    * Result: True. The threshold is breached.

2. Check the Cooldown:
    *Look at last_notified_at in the tracker. If a notification was sent 5 minutes ago, and your cooldown is 30 minutes, skip sending the notification but keep recording the raw data to InfluxDB.
    * If the cooldown has expired (or it's the first time the threshold was crossed), proceed to trigger the FCM push notification and update last_notified_at to the current time.

3. Evaluate Humidity (32.1%):
    * The rule says: Trigger if humidity < 20.0.
    * Result: False. Do nothing.

## 3. Resetting the Alert State
What happens when the sensor goes back to normal?If your backend loops through the rules and finds that the temperature is now $22.0^\circ\text{C}$ (which means the condition > 45.0 is now False), it checks the is_currently_triggered flag in your tracker.
If it was previously TRUE, your code knows the device has officially recovered. It can then flip is_currently_triggered back to FALSE and optionally send a pleasant recovery push notification to the user: "System Alert Resolved: Temperature is back within normal operating parameters."