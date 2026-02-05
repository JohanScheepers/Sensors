# ValveMe - 12V Solenoid Valve Control

A rugged node designed for remote irrigation or liquid flow control.

## Overview
ValveMe controls a high-current 12VDC solenoid valve using an integrated relay. It is ideal for automated watering systems, livestock drinking trough refills, or remote fluid transfer.

## Hardware Specifications
- **MCU**: ARM
- **Control Interface**: Relay Driver
- **Pin Mapping**: GPIO 10 (Relay), GPIO 11 (Status LED)
- **Operating Voltage**: 12VDC (External supply required for valve)

## Binary Data Payload

**Sensor Type ID:** 11

**7 bytes total**

| Byte 1 | Byte 2 | Byte 3 |
|---|---|---|---|
| Type (11) | Battery (uint8) | Valve Status (uint8) |

## Features
- **Active Power Tracking**: Monitors open duration to prevent overflow and estimate liquid volume.
- **Manual Override Support**: Responds to serial "OPEN" and "CLOSE" commands for manual control.
- **Status Indication**: Local LED visualizes valve state.

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.