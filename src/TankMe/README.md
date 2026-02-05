# TankMe - Water Level Monitor (0-10m)

A hydrostatic pressure-based solution for monitoring water levels in large storage tanks and reservoirs.

## Overview
TankMe measures the hydrostatic pressure of the water column to calculate the precise level in large storage tanks. It is capable of monitoring depths up to 10 meters with high precision.

## Hardware Specifications
- **MCU**: ARM
- **Level Sensor**: Analog Pressure Transducer (0-100 kPa)
- **Interface**: Pin **A0** (Analog Input)
- **VCC Supply**: 5.0V

## Binary Data Payload

**Sensor Type ID:** 9

**8 bytes total**

| Byte 1 | Byte 2 | Byte 3-4 | Byte 5-6 | Byte 7-8 |
|---|---|---|---|---|
| Type (9) | Battery (uint8) | Tank Level mm (uint16) |

## Features
- **Hydrostatic Precision**: Highly accurate level measurement based on liquid pressure.
- **Large Capacity**: Supports tanks and reservoirs up to 10 meters deep.
- **Stainless Steel Probe**: Corrosion-resistant pressure sensor housing for long-term submersion.

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.