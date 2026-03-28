# HumanMe

Monitoring of human presence and movement.

## Overview

HumanMe is a sensor node that monitors human presence and movement.

## Hardware

- **MCU**: STM32L0 series
- **Sensor**: HC-SR501 PIR sensor
- **Communication**: Semteck LR range
- **Power**: 3.3V and 2 AA batteries

## Software

- **PlatformIO**: PlatformIO for professional ARM-based embedded development.
- **Mesh**: Semteck LR range
- **Messaging**: UART (115200 baud)
- **Power**: Utilizes a TPS63051 (Starting point) to regulate 3.3V and 2 AA batteries for low-power mesh operation.

## Data Encoding

All sensor data is encoded in a compact binary format and sent over the mesh network.

**Byte 1 is always the Sensor Type**. The remaining bytes are the sensor-specific data payload.

| Sensor Type | Byte 1 Value |
| ----------- | ------------ |
| HumanMe     | 17           |

**HumanMe (4 bytes total)**

| Byte 1 | Byte 2 | Byte 3-4 | 
| ------ | -------- | -------- | 
| Type | Battery | mac address |  
