

<img src="./assets/icon.png" width="500"/>

# IOT Sensor Network

A comprehensive suite of IOT sensor nodes designed for agricultural and industrial monitoring. Built on the **ARM (STM32)** architecture and utilizing **BME280** sensors as base, these nodes communicate via a meshed UART JSON protocol.

<img src="./assets/box.webp" width="500"/>

## System Architecture

All nodes (except the Gateway) share a common base architecture:

- **Environment**: Bosch BME280 (Temp, Humidity, Pressure)
- **Messaging**: Standardized JSON over UART (115200 baud)
- **Power**: Optimized for battery and low-power mesh operation

## Sensor Catalog

### [DamMe](./src/DamMe)

Non-contact water level monitoring for dams and open water using ultrasonic ranging.

### [FenceMe](./src/FenceMe)

Safety-critical monitoring for electric fences up to 12kV. Includes local LED alert.

### [ForestRanger](./scr/ForestRanger)

Forest monitoring for wildfire detection and illegal logging and activities via ML on the edge.

### [FridgeMe](./src/FridgeMe)

Dual-zone monitoring for cold storage, featuring an external temperature probe.

### [GateMe](./src/GateMe)

Real-time security and operational status for gates and doors.

### [GatewayMe](./GatewayMe)

The primary bridge between the local mesh network and the internet. Features **Modular Connectivity** options:

- **[Integrated Ethernet](./GatewayMe/Ethernet)**: Waveshare UART TO ETH (S2E) for transparent bridging.
- **[Swappable NB-IoT](./GatewayMe/NB-IoT)**: SIM7000 module for cellular backhaul.
- **[Swappable LoRaWAN](./GatewayMe/LoRaWAN)**: Rak811 module for long-range WAN.

### [Mesh Network](./Mesh)

The low-power, long-range LoRa communication backbone for all sensor nodes.

### [MoistureMe](./src/MoistureMe)

Professional SDI-12 soil monitor for multi-depth moisture and temperature profiling.

### [RainMe](./src/RainMe)

Weather station node monitoring rainfall, wind speed/gust, and wind direction.

### [SwitchMe](./src/SwitchMe)

Remote-controlled logic output for activating external equipment.

### [TankMe](./src/TankMe)

Monitors water levels in large tanks (0-10m) using hydrostatic pressure sensing.

### [TempMe](./src/TempMe)

The base environmental node and mesh repeater. Measures temperature, humidity, pressure, and altitude.

### [TroughMe](./src/TroughMe)

Precision low-range monitoring (0-1.5m) for livestock drinking troughs.

### [ValveMe](./src/ValveMe)

Automated flow control for 12VDC solenoid valves.

### [SiloMe](./src/SiloMe)

Monitors levels in silos (0-15m) using ultrasonic rangefinder.

### [TrackMe](./src/TrackMe)

Tracking for live stock geo-location and fencing.

---

## Sensor Data Encoding

All sensor data is encoded in a compact binary format and sent over the mesh network.

**Byte 1 is always the Sensor Type**. The remaining bytes are the sensor-specific data payload.

| Sensor Type | Byte 1 Value |
| ----------- | ------------ |
| TempMe      | 0            |
| DamMe       | 1            |
| FenceME     | 2            |
| ForesRanger | 3            |
| FridgeMe    | 4            |
| GateMe      | 5            |
| MoistureMe  | 6            |
| RainMe      | 7            |
| SwitchMe    | 8            |
| TankMe      | 9            |
| TroughMe    | 10           |
| ValveMe     | 11           |
| SiloMe      | 12           |
| TrackMe     | 13           |

---

**Common Data Types:**

- Temperature: `int8_t` (raw data, ranges from -128 to 127°C)
- Humidity: `uint8_t` (0-100%)
- Pressure: `uint16_t` (hPa, e.g., 1013)
- Battery : `uint8_t` (V)
- Fence Voltage: `uint16_t` (kV)
- Gate Status: `uint8_t` (1=Open, 0=Closed)
- Soil Temp: `int8_t` (raw data, ranges from -128 to 127°C)
- Soil Moisture: `uint16_t` (raw data, ranges from 0 to 100%)
- Rainfall: `uint32_t` (total count of tips)
- Wind Speed: `uint8_t` (km/h)
- Wind Direction: `uint16_t` (degrees)
- Wind Gust: `uint8_t` (km/h)
- Switch Status: `uint8_t` (1=On, 0=Off)
- Distance: `uint16_t` (mm)
- Voltage/kV: `uint16_t` (kV \* 100)
- Latitude : `unint32_t` (lon)
- Longitude : `unint32_t` (lat)
- Speed: `uint8_t` (km/h)
- Course: `uint16_t` (degrees)
- hdop: `uint8_t` (0-100)
- Altitude: `uint16_t` (mm)
- Water Level: `uint16_t` (mm)
- Tank Level: `uint16_t` (mm)
- Valve Status: `uint8_t` (1=Open, 0=Closed)
- Silo Level: `uint16_t` (m)



**TempMe (6 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  |
| ------ | -------- | -------- | -------- | ------- |
| Type   | Air Temp | Humidity | Pressure | Battery |

**DamMe (8 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7-8       |
| ------ | -------- | -------- | -------- | ------- | -------------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Water Distance |

**FenceMe (8 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7-8      |
| ------ | -------- | -------- | -------- | ------- | ------------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Fence Voltage |

**ForestRanger (7 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7 |
| ------ | -------- | -------- | -------- | ------- | ------ |
| Type   | Air Temp | Humidity | Pressure | Battery |        |

**FridgeMe (7 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7      |
| ------ | -------- | -------- | -------- | ------- | ----------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Fridge Temp |

**GateMe (7 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7               |
| ------ | -------- | -------- | -------- | ------- | -------------------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Gate Status |

**MoistureMe (14 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7      | Byte 8      | Byte 9      | Byte 10     | Byte 11    | Byte 12    | Byte 13    | Byte 14    |
| ------ | -------- | -------- | -------- | ------- | ----------- | ----------- | ----------- | ----------- | ---------- | ---------- | ---------- | ---------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Soil Temp 1 | Soil Temp 2 | Soil Temp 3 | Soil Temp 4 | Soil Moisture 1 | Soil Moisture 2 | Soil Moisture 3 | Soil Moisture 4 |

**RainMe (13 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7-10         | Byte 11    | Byte 12   | Byte 13  |
| ------ | -------- | -------- | -------- | ------- | ----------------- | ---------- | --------- | -------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Rainfall | Wind Speed | Wind Gust | Wind Dir |

**SwitchMe (7 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7               |
| ------ | -------- | -------- | -------- | ------- | -------------------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Switch Status (1=On) |

**TankMe (8 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7-8        |
| ------ | -------- | -------- | -------- | ------- | --------------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Tank Level (mm) |

**TroughMe (8 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7-8         |
| ------ | -------- | -------- | -------- | ------- | ---------------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Water Level (mm) |

**ValveMe (7 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7                |
| ------ | -------- | -------- | -------- | ------- | --------------------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Valve Status (1=Open) |

**SiloMe (8 bytes total)**

| Byte 1 | Byte 2          | Byte 3           | Byte 4-5          | Byte 6  | Byte 7-8        |
| ------ | --------------- | ---------------- | ----------------- | ------- | --------------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Dist m |

**TrackMe (20 bytes total)**

| -    | Byte 1   | Byte 2   | Byte 3   | Byte 4-5 | Byte 6 | Bytes 7-10 | Bytes 11-14 | Bytes 15-16 | Bytes 17 | Bytes 18 | Bytes 19-20 |
| ---- | -------- | -------- | -------- | -------- | ------ | ---------- | ----------- | ----------- | -------- | -------- | ----------- |
| Type | Air Temp | Humidity | Pressure | Battery  | Lat    | Lon        | Course      |  Speed       | hdop     | sat | Altitude |

---

_Developed with PlatformIO for professional ARM-based embedded development._

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.
