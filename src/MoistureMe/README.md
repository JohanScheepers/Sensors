# MoistureMe - SDI-12 Multi-Depth Soil Monitor

A professional-grade soil monitoring node using the SDI-12 protocol to measure moisture and temperature at multiple depths.

## Overview
MoistureMe interfaces with high-precision multisensor probes (e.g., Sentek, Decagon, or Delta-T) via the **SDI-12** interface. It provides a vertical profile of soil moisture and soil temperature at 4 distinct depths, along with ambient atmospheric data.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Soil Probe**: SDI-12 Compliant Multisensor
- **Interface**: SDI-12 Bit-bang (Pin **GPIO 2**)
- **Baud Rate**: 1200 (Standard SDI-12)
- **Data Points**: 4x Soil Temp, 4x Moisture Readings

## Binary Data Payload

**Sensor Type ID:** 9

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6-13 | Byte 14-17 |
|---|---|---|---|---|---|
| Type (9) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Soil Temp 1-4 (4x int16) | Moisture 1-4 (4x uint8)|

## Features
- **SDI-12 Integration**: Supports industry-standard soil probes via the digital data interface.
- **Vertical Profiling**: Captures both moisture and temperature data at 4 depths to track water infiltration and thermal gradients.
- **Raw Data Passthrough**: Transmits uncalibrated digital values to allow for sophisticated backend modeling.
- **Atmospheric Context**: Combines multi-level soil data with air temperature, humidity, and pressure for complete environmental monitoring.
- **Low Power**: SDI-12 bus power management integrated into firmware.


## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.