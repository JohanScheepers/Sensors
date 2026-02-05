# FenceMe - High Voltage Fence Monitor

A critical safety and operational node for monitoring electric fence health.

## Overview
FenceMe measurements high-voltage pulses on an electric fence (up to 12kV). It provides immediate alerts if the fence voltage drops below a safe threshold, ensuring security and livestock containment.

## Hardware Specifications
- **MCU**: ARM
- **HV Sensor**: Voltage Divider + Optocoupler isolation circuit
- **Interface**: Analog Pin **A2**, GPIO 12 (Alert LED)
- **Max Input**: 12 kV (Scalable)

## Binary Data Payload

**Sensor Type ID:** 2

**4 bytes total**

| Byte 1 | Byte 2 | Byte 3-4 |
|---|---|---|
| Type (2) | Battery (uint8) | Voltage kV*100 (uint16)|

## Features
- **High Voltage Isolation**: Designed with optoisolation to protect the MCU from kV surges.
- **Continuous Monitoring**: Tracks peak pulse voltage.
- **Visual & Remote Alerts**: Local alert LED and UART push upon low-voltage detection (<3kV default).

> [!CAUTION]
> Electric fences carry high voltages. Ensure all connections follow strict safety guidelines and proper hardware isolation is used.


## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.