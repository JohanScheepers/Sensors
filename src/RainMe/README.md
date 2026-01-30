# RainMe - Rain Gauge Node

An automated rainfall monitoring station using a tipping bucket mechanism.

## Overview
RainMe interfaces with a reed-switch based tipping bucket to measure precipitation. It integrates environmental telemetry with real-time rainfall data to provide a complete weather profile.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Rain Sensor**: Magnetic Reed Switch (Interrupt driven)
- **Interface**: Pin **GPIO 3** (Internal Pull-up)
- **Detection**: Falling Edge Interrupt

## JSON UART Protocol
```json
{
  "id": "RAI01",
  "type": "RainMe",
  "t_c": 18.20,
  "h_pct": 88.50,
  "p_hpa": 1005.40,
  "rain_mm": 12.45
}
```

## Features
- **Interrupt Counting**: Reliable pulse counting handles high-frequency oscillation (debounced at 100ms).
- **Total Precipitation**: Tracks cumulative mm based on calibrated bucket volume (default 0.2794ml).
- **Weather Analysis**: Combines humidity and pressure data to correlate rainfall events with atmospheric changes.
- **Low Power**: High-efficiency sleep mode between rain events.
