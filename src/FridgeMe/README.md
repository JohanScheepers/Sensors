# FridgeMe - Cold Storage Monitor

A specialized temperature monitor for fridges, freezers, and cold store rooms.

## Overview
FridgeMe combines ambient environment monitoring with a highly accurate remote temperature probe. This allows the main unit to stay outside the refrigerated zone while the probe monitors critical internal temperatures.

<img src="./fridge_controller.png" width="600" />

## Hardware Specifications
- **MCU**: ARM
- **Ambient Sensor**: BME280 (I2C 0x76)
- **Internal Probe**: DS18B20 (Waterproof Stainless Steel)
- **Interface**: OneWire (Pin **GPIO 4**)

## Binary Data Payload

**Sensor Type ID:** 3

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6 |
|---|---|---|---|---|
| Type (3) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Probe Temp (int8)|

## Features
- **Remote Probing**: Allows monitoring deep inside freezers without compromising signal strength.
- **High Accuracy**: ±0.5°C accuracy from -10°C to +85°C.
- **Safety Alerts**: Automated warnings for temperature spikes (>5°C) or freezer failures.
- **Ambient Monitoring**: Tracks room conditions (humidity/temp) to identify condensation risks.
