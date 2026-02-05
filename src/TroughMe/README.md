# TroughMe - Trough Water Monitor (0-1.5m)

A precision low-range water level monitor designed specifically for livestock troughs and shallow water storage.

## Overview
TroughMe uses a high-sensitivity pressure sensor optimized for shallow depths. It provides granular measurements for water levels up to 1.5 meters, ensuring livestock have constant access to water.

## Hardware Specifications
- **MCU**: ARM
- **Level Sensor**: Analog Pressure Sensor (0-15 kPa range optimized)
- **Interface**: Pin **A0** (Analog Input)
- **VCC Supply**: 5.0V

## Binary Data Payload

**Sensor Type ID:** 10

**8 bytes total**

| Byte 1 | Byte 2 | Byte 3-4 |
|---|---|---|
| Type (10) | Battery (uint8) | Water Level mm (uint16) |

## Features
- **Shallow Water Optimization**: Optimized for 0-1.5m range for superior vertical resolution compared to standard tank sensors.
- **Livestock Safety**: Low voltage operation with no submerged electronic parts (pressure tube only).
- **Critical Alerts**: Immediate alerts for low trough levels.
- **Compact Integrated Base**: Built on the base TempMe architecture.

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.