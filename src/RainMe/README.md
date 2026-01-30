# RainMe - Weather Station Node

A comprehensive monitoring station for rainfall, wind speed, wind gust, and wind direction.

## Overview
RainMe transforms the standard environmental monitor into a high-performance weather station. It tracks precipitation via a tipping bucket mechanism and manages a full anemometer and wind vane set for atmospheric kinetic data.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Rain Sensor**: Tipping Bucket (Pin **GPIO 3**)
- **Anemometer**: Wind Speed Pulse (Pin **GPIO 14**)
- **Wind Vane**: Directional Analog (Pin **A3**)
- **Interface**: Interrupts (Rain/Wind), Analog (Direction)

## JSON UART Protocol
```json
{
  "id": "RAI01",
  "type": "RainMe",
  "t_c": 18.20,
  "h_pct": 88.50,
  "p_hpa": 1005.40,
  "rain_mm": 12.45,
  "wind_ms": 1.24,
  "windGust_ms": 5.40,
  "windDirection_d": 183
}
```

## Features
- **Precise Wind Tracking**: Uses dedicated interrupts to capture high-speed wind pulses.
- **Gust Analysis**: Calculates the relative peak wind intensity within each 60-second window.
- **Directional Profile**: 0-359° directional mapping for wind vector analysis.
- **Rain Profiling**: Interrupt-driven pulse counting for accurate precipitation tracking (mm/min).
- **Environment Fusion**: Combines humidity, pressure, and temperature to provide a holistic weather forecast profile.
