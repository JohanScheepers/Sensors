# TankMe - Water Level Monitor (0-10m)

A hydrostatic pressure-based solution for monitoring water levels in large storage tanks and reservoirs.

## Overview
TankMe measures the hydrostatic pressure of the water column to calculate the precise level in large storage tanks. It is capable of monitoring depths up to 10 meters with high precision.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Level Sensor**: Analog Pressure Transducer (0-100 kPa)
- **Interface**: Pin **A0** (Analog Input)
- **VCC Supply**: 5.0V

## Binary Data Payload

**Sensor Type ID:** 6

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6-7 |
|---|---|---|---|---|
| Type (6) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Water Level mm (uint16)|

## Features
- **Hydrostatic Precision**: Highly accurate level measurement based on liquid pressure.
- **Large Capacity**: Supports tanks and reservoirs up to 10 meters deep.
- **Stainless Steel Probe**: Corrosion-resistant pressure sensor housing for long-term submersion.
- **Integrated Environment Metrics**: Tracks air temperature and humidity at the tank site.
