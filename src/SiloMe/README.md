# SiloMe

A non-contact silo fill monitoring solution designed for silos (0-15m) using ultrasonic ranging.

## Hardware Specifications
- **MCU**: ARM
- **Level Sensor**: HC-SR04 or similar Ultrasonic Sensor
- **Trigger Pin**: GPIO 5
- **Echo Pin**: GPIO 6
- **Max Range**: 400 cm (4 meters)

## Binary Data Payload

**Sensor Type ID:** 12

**8 bytes total**

| Byte 1  | Byte 2 | Byte 3-4 |
|---|---|---|
| Type (12) | Battery (uint8) | Dist m (uint16) |

## Features
- **Non-Contact Sensing**: High reliability in varying silo levels.
- **Rugged Design**: Optimized for outdoor deployment near open water bodies.


## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.