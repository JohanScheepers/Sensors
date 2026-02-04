# PivotMe

Monitoring pivot irrigation systems for movement, water usage and pressure.

## Hardware Specification

- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **GPS**: NEO-M8N
- **Ultrasonic Water Meter**:
- **Pressure Sender Sensor 0-10 bar**: 

## Binary Data Payload

**Sensor Type ID:** 14

**26 bytes total**

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6 | Bytes 7-10 | Bytes 11-14 | Bytes 15-16 | Byte 17 | Byte 18 | Bytes 19-20 | Bytes 21-22 | Bytes 23-26 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Type (14) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Battery (uint8) | Lat (uint32) | Lon (uint32) | Course (uint16) | Speed (uint8) | hdop (uint8) | sat | Altitude (uint16) | Pressure (uint16) | Meter (uint32) |