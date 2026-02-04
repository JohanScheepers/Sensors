# TrackMe

Tracking for live stock geo-location and fencing.

## Hardware Specification

- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **GPS**: NEO-M8N

## Binary Data Payload

**Sensor Type ID:** 13

| -    | Byte 1   | Byte 2   | Byte 3   | Byte 4-5 | Byte 6 | Bytes 7-10 | Bytes 11-14 | Bytes 15-16 | Bytes 17 | Bytes 18 | Bytes 19-20 |
| ---- | -------- | -------- | -------- | -------- | ------ | ---------- | ----------- | ----------- | -------- | -------- | ----------- |
| Type | Air Temp | Humidity | Pressure | Battery  | Lat    | Lon        | Course      |  Speed       | hdop     | sat | Altitude |