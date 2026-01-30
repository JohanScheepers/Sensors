# TankMe - Water Level Monitor (0-10m)

A specialized node for monitoring water levels in large storage tanks or wells up to 10 meters deep.

## Overview
TankMe builds upon the **TempMe** base, adding a submersible pressure sensor. By measuring the hydrostatic pressure at the bottom of the tank, it accurately calculates the water level and percentage full.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Level Sensor**: Analog Submersible Pressure Transducer (0-100 kPa)
- **Interface**: Pin **A0** (Voltage divider / Analog Input)
- **Input Voltage**: 5.0V (Standardized)

## JSON UART Protocol
```json
{
  "id": "TNK01",
  "type": "TankMe",
  "t_c": 22.10,
  "h_pct": 50.40,
  "p_hpa": 1012.80,
  "lvl_m": 5.40
}
```

## Features
- **Hydrostatic Calculation**: Converts kPa to meters of water (approx 9.8 kPa per meter).
- **Environmental Context**: Includes ambient temperature, humidity, and air pressure for complete monitoring.
- **Battery Optimization**: Powers the analog sensor only during readings to preserve battery.
- **Alert System**: Low-level warnings configurable in firmware.
