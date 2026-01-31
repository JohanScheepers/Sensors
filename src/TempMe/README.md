# TempMe - Environmental Monitoring Node

The base unit for the IOT sensor network. It provides ambient environmental data and acts as a mesh network repeater.

## Overview
TempMe uses a **BME280** sensor to monitor barometric pressure, humidity, and temperature. It is designed for low-power battery operation and serves as the structural base for most other specialized sensors in the family.

## Hardware Specifications
- **MCU**: ARM (STM32/STM32L0 series)
- **Primary Sensor**: Bosch BME280
- **Communication**: UART (transmitting to mesh radio)
- **Interface**: I2C (address 0x76)
- **Power**: Battery optimized

## Binary Data Payload

**Sensor Type ID:** 0

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6-7 |
|---|---|---|---|---|
| Type (0) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Altitude (int16)|

## Features
- **Celsius Precision**: All temperature readings are strictly in °C.
- **Mesh Ready**: Designed to plug directly into mesh radio modules.
- **Interval**: Default 60-second telemetry update.
- **Compact Build**: Small footprint for versatile deployment.
