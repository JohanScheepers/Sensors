# TrackMe

Tracking for live stock geo-location and fencing.

## Hardware Specification

- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **GPS**: NEO-M8N

## Binary Data Payload

**Sensor Type ID:** 13

**20 bytes total**

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6 | Bytes 7-10 | Bytes 11-14 | Bytes 15-16 | Byte 17 | Byte 18 | Bytes 19-20 |
|---|---|---|---|---|---|---|---|---|---|---|
| Type (13) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Battery (uint8) | Lat (uint32) | Lon (uint32) | Course (uint16) | Speed (uint8) | hdop (uint8) | sat | Altitude (uint16) |