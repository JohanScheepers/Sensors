# SolarMe

Monitoring of MPPT solar chargers

## Overview
SolarMe provides a remote monitoring of MPPT solar chargers

## Hardware Specifications
- **MCU**: ARM
- **SolarMe Input/Output**: UART

https://github.com/Fabian-Schmidt/esphome-victron_ble

## Binary Data Payload

**Sensor Type ID:** 16

| Byte 1 | Byte 2 | Byte 3-4 | Byte 5-6 | Byte 7 | Byte 8-9 | Byte 10-11 | Byte 12-13 | Byte 14-15 | Byte 16-17 | Byte 18 | Byte 19 | Byte 20-21 |
| ------ | -------- | ---| ---| ---| ---| ---| ---| ---| ---| ---| ---| ---|
| Type (16) | Battery (uint8) | AUX Voltage (uint16) | Battery Voltage (uint16) | State of Charge in % (uint8) | Battery time remaining (uint16) | Consumed Ah (uint32) | Battery Current (int16) | Yield Today (uint32) | PV Power (uint16) | Device State (Off, Bulk, Absorption, Float ...) (uint8) | Load output (uint8) | 

|Category	|Readable Data (Monitoring)|
|---|---|
|Real-Time Operation	|Solar panel wattage and voltage|	
||Battery voltage and charge current|	
||Current charge stage (Bulk, Absorption, Float)|

## Features

-**Precise MPPT Solar Charger Monitoring**: Monitors solar panel wattage and voltage, battery voltage and charge current, and current charge stage (Bulk, Absorption, Float).

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.