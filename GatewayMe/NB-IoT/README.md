# NB-IoT Connectivity Module

## Overview
This swappable module provides Narrowband IoT (NB-IoT) connectivity for the GatewayMe system. It allows the gateway to communicate with the cloud backend in areas where Ethernet is unavailable or as a backup connection.

## Interface
- **Connection Type**: UART (Universal Asynchronous Receiver-Transmitter)
- **Connected To**: Mesh Controller (Main Gateway Board)
- **Function**: Transmits serialized JSON telemetry from the mesh network to the cloud and receives OTA commands.

## Hardware Specifications
- **Module Type**: Swappable NB-IoT modem (e.g., SIM7000, BC95)
- **Antenna**: SMA connector for external NB-IoT antenna
- **Power**: Powered via the main GatewayMe board
