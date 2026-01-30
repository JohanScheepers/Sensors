# MoistureMe - Soil Moisture Monitor

A precision irrigation sensor for monitoring soil hydration levels.

## Overview
MoistureMe uses a capacitive soil moisture sensor to provide highly reliable, corrosion-resistant hydration data. It categorizes soil health to help optimize watering schedules.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Soil Sensor**: Capacitive Moisture Sensor (v1.2 or similar)
- **Interface**: Analog Pin **A1**
- **Voltage**: 3.3V-5V Compatible

## JSON UART Protocol
```json
{
  "id": "MOI01",
  "type": "MoistureMe",
  "t_c": 23.40,
  "h_pct": 48.20,
  "p_hpa": 1013.25,
  "moi_pct": 65.40
}
```

## Features
- **Capacitive Technology**: Eliminates probe corrosion common in resistive sensors.
- **Moisture Classification**: Maps analog levels to 0-100% based on calibrated DRY/WET thresholds.
- **Air Metrics**: Combines soil moisture with air temperature and humidity for complete evapotranspiration modeling.
- **Power Efficient**: Duty-cycles the probe to prevent electrical noise and save power.
