# DamMe - Dam & Water Level Monitor (Ultrasonic)

A non-contact water level monitoring solution designed for dams, reservoirs, or open containers.

## Overview
DamMe utilizes high-frequency sound waves to measure the distance to the water surface. This non-contact method is ideal for environments where sensors cannot be easily submerged or where water debris might interfere with contact sensors.

<img src="./dam_controller.png" width="600" />

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Level Sensor**: HC-SR04 or similar Ultrasonic Sensor
- **Trigger Pin**: GPIO 5
- **Echo Pin**: GPIO 6
- **Max Range**: 400 cm (4 meters)

## Binary Data Payload

**Sensor Type ID:** 2

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6-7 |
|---|---|---|---|---|
| Type (2) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Water Dist mm (uint16)|

## Features
- **Non-Contact Sensing**: High reliability in varying water quality conditions.
- **Air Density Compensation**: Uses BME280 temperature data to calibrate the speed of sound for higher accuracy.
- **Dual Monitoring**: Tracks both water distance and ambient environmental metrics.
- **Rugged Design**: Optimized for outdoor deployment near open water bodies.
