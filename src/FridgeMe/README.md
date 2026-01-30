# FridgeMe - Cold Storage Monitor

A specialized temperature monitor for fridges, freezers, and cold store rooms.

## Overview
FridgeMe combines ambient environment monitoring with a highly accurate remote temperature probe. This allows the main unit to stay outside the refrigerated zone while the probe monitors critical internal temperatures.

## Hardware Specifications
- **MCU**: ARM
- **Ambient Sensor**: BME280 (I2C 0x76)
- **Internal Probe**: DS18B20 (Waterproof Stainless Steel)
- **Interface**: OneWire (Pin **GPIO 4**)

## JSON UART Protocol
```json
{
  "id": "FRI01",
  "type": "FridgeMe",
  "amb_t_c": 22.50,
  "h_pct": 42.10,
  "p_hpa": 1013.25,
  "probe_t_c": -18.40
}
```

## Features
- **Remote Probing**: Allows monitoring deep inside freezers without compromising signal strength.
- **High Accuracy**: ±0.5°C accuracy from -10°C to +85°C.
- **Safety Alerts**: Automated warnings for temperature spikes (>5°C) or freezer failures.
- **Ambient Monitoring**: Tracks room conditions (humidity/temp) to identify condensation risks.
