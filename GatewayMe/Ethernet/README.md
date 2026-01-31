# Integrated Ethernet Connectivity

## Overview
Powering the GatewayMe's primary connection to the internet is an integrated Ethernet interface. This provides a stable, high-speed backhaul for aggregating sensor data and is the preferred connection method when available.

## Interface
- **Connection Type**: Integrated RJ45 Port
- **Connected To**: Direct integration with the Gateway Controller (STM32/ESP32)
- **Function**: Primary WAN uplink for JSON telemetry transmission and remote OTA management.

## Hardware Specifications
- **Controller**: W5500 SPI Ethernet Controller or RMII PHY (depending on board revision)
- **Speed**: 10/100 Mbps
- **Features**: 
  - Hardware TCP/IP Stack (if W5500)
  - Supports Static IP and DHCP
  - LED indicators for Link and Activity on the jack
