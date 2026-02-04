# CO2Me - Carbon Dioxide & VOC Monitor

Monitoring CO2 levels and Volatile Organic Compounds (VOC) in greenhouses, warehouses, and industrial environments.

## Overview
CO2Me is designed to ensure optimal air quality for plant growth in greenhouses or safety in enclosed workspaces. It measures CO2 concentrations and total VOCs alongside standard environmental metrics (temperature, humidity, pressure).

## Hardware Specifications
- **MCU**: Arm® Cortex®‑M0+ (STM32L0 series)
- **Primary Sensor**: CO2/VOC Sensor (e.g., SCD30 or SGP30)
- **Environment Sensor**: Bosch BME280
- **Communication**: UART (transmitting to mesh radio)

## Binary Data Payload

**Sensor Type ID:** 15

**10 bytes total**

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6 | Byte 7-8 | Byte 9-10 |
|---|---|---|---|---|---|---|
| Type (15) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Battery (uint8) | CO2 (uint16) | VOC (uint16) |

## Features
- **Air Quality Monitoring**: Real-time tracking of CO2 levels in ppm.
- **VOC Detection**: Monitors volatile organic compounds for safety and health.
- **Environmental Context**: Includes ambient temperature, humidity, and pressure for comprehensive climate analysis.
- **Low Power**: Optimized for long-term battery-powered deployment.

## License

This project is proprietary and confidential. All Rights Reserved. See the [LICENSE](LICENSE) file for details.