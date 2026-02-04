# SiloMe

A non-contact silo fill monitoring solution designed for silos (0-15m) using ultrasonic ranging.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Level Sensor**: HC-SR04 or similar Ultrasonic Sensor
- **Trigger Pin**: GPIO 5
- **Echo Pin**: GPIO 6
- **Max Range**: 400 cm (4 meters)

## Binary Data Payload

**Sensor Type ID:** 12

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6-7 |
|---|---|---|---|---|
| Type (2) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Dist m (uint16)|

## Features
- **Non-Contact Sensing**: High reliability in varying silo levels.
- **Air Density Compensation**: Uses BME280 temperature data to calibrate the speed of sound for higher accuracy.
- **Dual Monitoring**: Tracks both water distance and ambient environmental metrics.
- **Rugged Design**: Optimized for outdoor deployment near open water bodies.


## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.