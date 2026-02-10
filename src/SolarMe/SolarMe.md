# SolarMe

Monitoring of MPPT solar chargers

## Overview
SolarMe provides a remote monitoring of MPPT solar chargers

## Hardware Specifications
- **MCU**: ESP32 (Required for efficient BLE scanning / standard Ranger STM32L0 with BLE Module) or Compatible BLE Observer
- **Input Interface**: Bluetooth Low Energy (BLE) - Victron Proprietary Protocol
- **Output Interface**: Ranger Mesh (UART/Semtech LoRa)

> **Integration Note**: This sensor implementation leverages the `esphome-victron_ble` component to listen for Victron advertisements.
> Reference: [Fabian-Schmidt/esphome-victron_ble](https://github.com/Fabian-Schmidt/esphome-victron_ble)

## Binary Data Payload

**Sensor Type ID:** 16

| Byte 1 | Byte 2 | Byte 3-4 | Byte 5-6 | Byte 7 | Byte 8-9 | Byte 10-13 | Byte 14-15 | Byte 16-19 | Byte 20-21 | Byte 22 | Byte 23 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Type**<br>(0x10) | **Battery**<br>(Node %) | **Aux Voltage**<br>(mV, uint16) | **Batt Voltage**<br>(mV, uint16) | **SoC**<br>(%, uint8) | **Time Rem**<br>(mins, uint16) | **Consumed Ah**<br>(Ah * 10?, uint32) | **Batt Current**<br>(mA, int16) | **Yield Today**<br>(Wh, uint32) | **PV Power**<br>(W, uint16) | **Dev State**<br>(Enum, uint8) | **Load Out**<br>(Enum, uint8) |

### Data Parsing Guide
- **Aux Voltage**: `val / 100` (V)
- **Battery Voltage**: `val / 100` (V)
- **Battery Current**: `val / 10` (A)
- **Device State**:
  - `0`: Off
  - `2`: Fault
  - `3`: Bulk
  - `4`: Absorption
  - `5`: Float
  - `9`: Inverting

## Features

- **Precise MPPT & Battery Monitoring**: Monitors solar panel wattage, battery voltage, charge current, and charge stage.
- **Wireless Integration**: Connects via BLE to Victron SmartSolar and SmartShunt devices.
- **Ranger Mesh Compatible**: Relays local energy data to the central gateway using the standard binary payload.

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.