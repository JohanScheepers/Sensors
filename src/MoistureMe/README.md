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

## JSON UART Protocol
Telemetery is transmitted in raw digital format. Calibration (Wet/Dry) is handled by the cloud backend.

```json
{
  "id": "MOI01",
  "type": "MoistureMe",
  "t_c": 23.40,
  "h_pct": 48.20,
  "p_hpa": 1013.25,
  "soil_t_c": [21.30, 20.80, 19.50, 18.20],
  "moi_raw": [34.50, 32.10, 28.50, 25.00]
}
```

## Features
- **SDI-12 Integration**: Supports industry-standard soil probes via the digital data interface.
- **Vertical Profiling**: Captures both moisture and temperature data at 4 depths to track water infiltration and thermal gradients.
- **Raw Data Passthrough**: Transmits uncalibrated digital values to allow for sophisticated backend modeling.
- **Atmospheric Context**: Combines multi-level soil data with air temperature, humidity, and pressure for complete environmental monitoring.
- **Low Power**: SDI-12 bus power management integrated into firmware.
