# ValveMe - 12V Solenoid Valve Control

A rugged node designed for remote irrigation or liquid flow control.

## Overview
ValveMe controls a high-current 12VDC solenoid valve using an integrated relay. It is ideal for automated watering systems, livestock drinking trough refills, or remote fluid transfer.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Control Interface**: Relay Driver
- **Pin Mapping**: GPIO 10 (Relay), GPIO 11 (Status LED)
- **Operating Voltage**: 12VDC (External supply required for valve)

## JSON UART Protocol
```json
{
  "id": "VAL01",
  "type": "ValveMe",
  "t_c": 28.50,
  "h_pct": 32.20,
  "p_hpa": 1011.80,
  "open": false
}
```

## Features
- **Active Power Tracking**: Monitors open duration to prevent overflow and estimate liquid volume.
- **Manual Override Support**: Responds to serial "OPEN" and "CLOSE" commands for manual control.
- **Environment Interlock**: Telemetry allows for logic and safety checks (e.g., disable valve if temp < 2°C to prevent freezing).
- **Status Indication**: Local LED visualizes valve state.
