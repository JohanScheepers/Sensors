# GatewayMe - Mesh Network Bridge

The primary coordinator and internet gateway for the IOT sensor network.

## Overview
GatewayMe serves as the central bridge between the local autonomous mesh network and the internet. It aggregates JSON telemetry from all sensor nodes and forwards it to the cloud backend via a secure Ethernet connection.

## Hardware Specifications
- **Connectivity**: Integrated RJ45 Ethernet Port (W5500 or similar)
- **Mesh Radio**: LoRa / RF coordinate module (SMA Antenna connector)
- **Power**: Standard AC 110/220V with DC regulation
- **Indication**: Power, Link, and Data RX/TX LEDs

## Build Configuration
Note that **GatewayMe** is built as a separate project from the sensor nodes due to its unique networking stack requirements.

- **Network Stack**: DHCP/Static IP Ethernet support
- **Data Protocol**: JSON parsing and MQTT/HTTP passthrough
- **Architecture**: Specialized Ethernet-capable board (e.g., STM32 Nucleo with Ethernet)

## Features
- **Central Coordinator**: Manages mesh network routing and node registration.
- **Ethernet Persistence**: Optimized for long-term stable internet connectivity.
- **Data Aggregator**: Buffers and serializes incoming node data for backend transmission.
- **Remote Commands**: Capable of sending OTA commands (e.g., "ON/OFF", "OPEN/CLOSE") back into the mesh network.
