

<img src="./assets/icon.png" width="500"/>

# IOT Sensor Network

A comprehensive suite of IOT sensor nodes designed for agricultural and industrial monitoring. Built on the **Semteck LR** range architecture with support for **ARM (STM32)** architecture and utilizing **BME280** sensors as base, these nodes communicate via a mesh protocol.

<img src="./assets/box.webp" width="500"/>

## System Architecture

All nodes (except the Gateway) share a common base architecture:

- **Mesh**: Semteck LR range
- **MCU**: Arm® Cortex®‑M0+ (STM32L0 series)  (Not equipped as standard)
- **Environment**: Bosch BME280 (Temp, Humidity, Pressure) (Not equipped as standard)
- **Messaging**: UART (115200 baud)
- **Power**: Utilizes a TPS63051 (Starting point) to regulate 3.3V and 2 AA batteries for low-power mesh operation.

## Sensor Catalog

### [DamMe](./src/DamMe)

Non-contact water level monitoring for dams and open water using ultrasonic ranging.

### [FenceMe](./src/FenceMe)

Safety-critical monitoring for electric fences up to 12kV. Includes local LED alert.

### [ForesRanger](./src/ForesRanger)

Forest monitoring for wildfire detection and illegal logging and activities via ML on the edge.

### [FridgeMe](./src/FridgeMe)

Dual-zone monitoring for cold storage, featuring an external temperature probe.

### [GateMe](./src/GateMe)

Real-time security and operational status for gates and doors.

### [RepeatMe](./src/RepeatMe)

It only repeats the signal from other sensors to the rest of the mesh network and the gateway. 

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

The base environmental node and mesh repeater. Measures temperature, humidity and pressure.

### [TroughMe](./src/TroughMe)

Precision low-range monitoring (0-1.5m) for livestock drinking troughs.

### [ValveMe](./src/ValveMe)

Automated flow control for 12VDC solenoid valves.

### [SiloMe](./src/SiloMe)

Monitors levels in silos (0-15m) using ultrasonic rangefinder.

### [TrackMe](./src/TrackMe)

Tracking for live stock geo-location and fencing.

### [PivotMe](./src/PivotMe)

Monitoring pivot irrigation systems for movement, water usage and pressure.

### [CO2Me](./src/CO2Me)

Monitoring CO2 levels in greenhouses and warehouses.

### [SolarMe](./src/SolarME)

Monitoring of MPPT solar charger

### [HumanMe](./src/HumanMe)

Monitoring of human presence and movement.

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
| PivotMe     | 14           |
| CO2Me       | 15           |
| SolarMe     | 16           |
| HumanMe     | 17           |

---

**Common Data Types:**

- Temperature: `int8_t` (raw data, ranges from -128°C to 127°C)
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
- Latitude : `uint32_t` (°)
- Longitude : `uint32_t` (°)
- Speed: `uint8_t` (km/h)
- Course: `uint16_t` (°)
- hdop: `uint8_t` (0-100)
- Altitude: `uint16_t` (mm)
- Water Level: `uint16_t` (mm)
- Tank Level: `uint16_t` (mm)
- Valve Status: `uint8_t` (1=Open, 0=Closed)
- Silo Level: `uint16_t` (m)
- Meter: `uint32_t` (m<sup>3</sup>)
- CO2: `uint16_t` (ppm)
- VOC: `uint16_t` (ppm)
- AUX Voltage: `uint16_t` (V)
- Battery Voltage: `uint16_t` (V)
- State of Charge in %: `uint8_t` (%)
- Battery time remaining: `uint16_t` (h)
- Consumed Ah: `uint32_t` (Ah)
- Battery Current: `int16_t` (A)
- Yield Today: `uint32_t` (kWh)
- PV Power: `uint16_t` (W)
- Device State: `uint8_t` (0=Off, 1=Bulk, 2=Absorption, 3=Float)
- Load output: `uint8_t` (1=On, 0=Off)

**RepeaterMe**

It only repeats the signal from other sensors to the rest of the mesh network and the gateway.

**TempMe (6 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  |
| ------ | -------- | -------- | -------- | ------- |
| Type   | Air Temp | Humidity | Pressure | Battery |

**DamMe (4 bytes total)**

| Byte 1  | Byte 2  | Byte 3-4       |
| ------ | ------- | -------------- |
| Type   | Battery | Water Distance |

**FenceMe (4 bytes total)**

| Byte 1  | Byte 2  | Byte 3-4       |
| ------ | ------- | -------------- |
| Type   | Battery | Fence Voltage |

**ForestRanger (7 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7 |
| ------ | -------- | -------- | -------- | ------- | ------ |
| Type   | Air Temp | Humidity | Pressure | Battery |   TBA     |

**FridgeMe (7 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7      |
| ------ | -------- | -------- | -------- | ------- | ----------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Fridge Temp |

**GateMe (4 bytes total)**

| Byte 1 | Byte 2  | Byte 3-4       |
| ------ | ------- | -------------- |
| Type   | Battery | Gate Status |

**MoistureMe (14 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7      | Byte 8      | Byte 9      | Byte 10     | Byte 11    | Byte 12    | Byte 13    | Byte 14    |
| ------ | -------- | -------- | -------- | ------- | ----------- | ----------- | ----------- | ----------- | ---------- | ---------- | ---------- | ---------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Soil Temp 1 | Soil Temp 2 | Soil Temp 3 | Soil Temp 4 | Soil Moisture 1 | Soil Moisture 2 | Soil Moisture 3 | Soil Moisture 4 |

**RainMe (13 bytes total)**

| Byte 1 | Byte 2   | Byte 3   | Byte 4-5 | Byte 6  | Byte 7-10         | Byte 11    | Byte 12   | Byte 13  |
| ------ | -------- | -------- | -------- | ------- | ----------------- | ---------- | --------- | -------- |
| Type   | Air Temp | Humidity | Pressure | Battery | Rainfall | Wind Speed | Wind Gust | Wind Dir |

**SwitchMe (3 bytes total)**

| Byte 1  | Byte 2  | Byte 3     |
| ------ | ------- | ---------- |
| Type   | Battery | Switch Status (1=On) |

**TankMe (4 bytes total)**

| Byte 1  | Byte 2  | Byte 3-4       |
| ------ | ------- | -------------- |
| Type   | Battery | Tank Level (mm) |

**TroughMe (4 bytes total)**

| Byte 1  | Byte 2  | Byte 3-4         |
| ------ | ------- | ---------------- |
| Type   | Battery | Water Level (mm) |

**ValveMe (4 bytes total)**

| Byte 1  | Byte 2  | Byte 3-4       |
| ------ | ------- | -------------- |
| Type   | Battery | Valve Status (1=Open) |

**SiloMe (4 bytes total)**

| Byte 1  | Byte 2  | Byte 3-4       |
| ------ | ------- | -------------- |
| Type   | Battery | Dist m |

**TrackMe (20 bytes total)**

| Byte 1   | Byte 2   | Byte 3   | Byte 4-5 | Byte 6 | Bytes 7-10 | Bytes 11-14 | Bytes 15-16 | Bytes 17 | Bytes 18 | Bytes 19-20 |
| ---- | -------- | -------- | -------- | -------- | ------ | ---------- | ----------- | ----------- | -------- | -------- | ----------- |
| Type | Air Temp | Humidity | Pressure | Battery  | Lat    | Lon        | Course      |  Speed       | hdop     | sat | Altitude |

**PivotMe (26 bytes total)**

| Byte 1    | Byte 2 | Bytes 3-6 | Bytes 7-10 | Bytes 11-12 | Bytes 13 | Bytes 14 | Bytes 15-16 | Bytes 17-18 | Bytes 19-22 |
| ---- | -------- | ------ | ---------- | ----------- | ----------- | -------- | -------- | ----------- | ---|---|
| Type  | Battery  | Lat    | Lon        | Course      |  Speed       | hdop     | sat | Altitude | Pressure | Meter |

**CO2Me (10 bytes total)**

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6 | Byte 7-8 | Byte 9-10 |
| ------ | -------- | -------- | -------- | ------- | -------- | --------- |
| Type | Air Temp | Humidity | Pressure | Battery | CO2 | VOC |

**SolarMe (22 bytes total)**

| Byte 1 | Byte 2 | Byte 3-4 | Byte 5-6 | Byte 7 | Byte 8-9 | Byte 10-11 | Byte 12-13 | Byte 14-15 | Byte 16-17 | Byte 18 | Byte 19 | Byte 20-21 |
| ------ | -------- |----|----|----|----|----|----|----|----|----|----|----|
| Type | Battery | AUX Voltage | Battery Voltage | State of Charge in % | Battery time remaining | Consumed Ah | Battery Current | Yield Today | PV Power | Device State (Off, Bulk, Absorption, Float ...) |  Load output |

**HumanMe (4 bytes total)**

| Byte 1 | Byte 2 | Byte 3-8 | 
| ------ | -------- | -------- | 
| Type | Battery | mac address |  

---

_Developed with PlatformIO for professional ARM-based embedded development._

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.
