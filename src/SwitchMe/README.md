# SwitchMe - Remote GPIO Control Node

A software-controllable switch for remote device activation over the mesh network.

## Overview
SwitchMe provides a remote-controlled logic output (TTL) and a status LED. It allows the central gateway to trigger external relays or status indicators while simultaneously providing local environmental telemetry.

## Hardware Specifications
- **MCU**: ARM
- **Switch Output**: GPIO Digital Output
- **Pin Mapping**: GPIO 8 (Output), GPIO 9 (Status LED)

## Binary Data Payload

**Sensor Type ID:** 8

**7 bytes total**

| Byte 1 | Byte 2 | Byte 3 |
|---|---|---|
| Type (8) | Battery (uint8) | Switch Status (uint8) |

## Features
- **Remote Command Processing**: Listens for "ON" and "OFF" serial commands via UART.
- **Visual Feedback**: Built-in status LED reflects the actual state of the switch.
- **Fail-Safe**: Default state (LOW/OFF) on startup.


## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.