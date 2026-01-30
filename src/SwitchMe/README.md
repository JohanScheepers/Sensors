# SwitchMe - Remote GPIO Control Node

A software-controllable switch for remote device activation over the mesh network.

## Overview
SwitchMe provides a remote-controlled logic output (TTL) and a status LED. It allows the central gateway to trigger external relays or status indicators while simultaneously providing local environmental telemetry.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Switch Output**: GPIO Digital Output
- **Pin Mapping**: GPIO 8 (Output), GPIO 9 (Status LED)

## JSON UART Protocol
```json
{
  "id": "SWI01",
  "type": "SwitchMe",
  "t_c": 26.40,
  "h_pct": 38.00,
  "p_hpa": 1012.80,
  "on": true
}
```

## Features
- **Remote Command Processing**: Listens for "ON" and "OFF" serial commands via UART.
- **Visual Feedback**: Built-in status LED reflects the actual state of the switch.
- **Integrated Monitoring**: Reports ambient conditions to ensure the switched environment (e.g., equipment cabinet) is within operating range.
- **Fail-Safe**: Default state (LOW/OFF) on startup.
