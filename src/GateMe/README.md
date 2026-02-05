# GateMe - Gate & Door Status Monitor

A security and operational node for tracking the state of gates, doors, or windows.

## Overview
GateMe utilizes a magnetic contact switch to determine if a gate is open or closed. It tracks the duration of open states and provides real-time alerts for state changes.

## Hardware Specifications
- **MCU**: ARM
- **Contact Sensor**: Magnetic Reed Switch / Hall Effect
- **Interface**: Pin **GPIO 7** (Internal Pull-up)

## Binary Data Payload

**Sensor Type ID:** 5

**4 bytes total**

| Byte 1 | Byte 2 | Byte 3-4 |
|---|---|---|
| Type (5) | Battery (uint8) | Status (uint8) |

## Features
- **State Change Detection**: Immediate UART broadcast upon gate opening/closing.
- **Duration Tracking**: Reports how long (in seconds) the gate has been in its current state.
- **Extended Open Alert**: Logic included to flag gates left open longer than a threshold (default 5 min).
- **Environment Context**: Useful for monitoring perimeter gates or barn doors.


## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.