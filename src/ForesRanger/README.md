# ForesRanger - Forest Monitoring & Wildfire Detection

Early detection of forest fires and illegal logging using ML on the edge.

## Overview
ForesRanger is an advanced monitoring node designed for large-scale forest protection. It utilizes embedded AI to detect the chemical signatures of fires and the acoustic signatures of chainsaws or vehicles, providing ultra-early warnings.

## Hardware Specifications
- **MCU**: Arm® Cortex®‑M0+ with specialized ML capabilities
- **Atmospheric Sensor**: Bosch BME280 (I2C 0x76)
- **Gas Sensor**: Multi-gas sensor for combustion signature detection
- **Acoustic Sensor**: High-sensitivity MEMS microphone
- **Communication**: UART (transmitting to mesh radio)

## Binary Data Payload

**Sensor Type ID:** 3

**7 bytes total**

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6 | Byte 7 |
|---|---|---|---|---|---|
| Type (3) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Battery (uint8) | Alert Code (uint8) |

## Features
- **Embedded AI Fire Detection**: Detects gas and environmental anomalies on the edge.
- **Embedded AI Acoustic Detection**: Detects logging activities and vehicle movement.
- **Autonomous Mesh Network**: Operates as both a sensor and a repeater in a low-power mesh.
- **High Durability**: Designed for long-term outdoor deployment in harsh environments.

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.
