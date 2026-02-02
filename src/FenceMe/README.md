# FenceMe - High Voltage Fence Monitor

A critical safety and operational node for monitoring electric fence health.

## Overview
FenceMe measurements high-voltage pulses on an electric fence (up to 12kV). It provides immediate alerts if the fence voltage drops below a safe threshold, ensuring security and livestock containment.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **HV Sensor**: Voltage Divider + Optocoupler isolation circuit
- **Interface**: Analog Pin **A2**, GPIO 12 (Alert LED)
- **Max Input**: 12 kV (Scalable)

## Binary Data Payload

**Sensor Type ID:** 10

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6-7 |
|---|---|---|---|---|
| Type (10) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Voltage kV*100 (uint16)|

## Features
- **High Voltage Isolation**: Designed with optoisolation to protect the MCU from kV surges.
- **Continuous Monitoring**: Tracks peak pulse voltage.
- **Visual & Remote Alerts**: Local alert LED and JSON push upon low-voltage detection (<3kV default).
- **Historical Analysis**: Correlation of fence voltage with environmental moisture (humidity/rain).

> [!CAUTION]
> Electric fences carry high voltages. Ensure all connections follow strict safety guidelines and proper hardware isolation is used.


## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.