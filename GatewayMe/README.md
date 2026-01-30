# GatewayMe - Separate Configuration

The GatewayMe gateway is **not** part of the standard PlatformIO sensor build configuration. It has different requirements:

## Hardware Specification
- **Connectivity**: 1x RJ45 Ethernet Port
- **Power**: AC 110/220V
- **Antenna**: 1x SMA connector for mesh network antenna
- **Purpose**: Acts as the main bridge between the mesh network and the internet

## Build Configuration

GatewayMe requires a separate build configuration due to:
- Different hardware platform (Ethernet-capable board)
- Different firmware requirements (gateway vs. sensor node)
- Network stack dependencies

> [!NOTE]
> Create a separate PlatformIO project or build configuration for GatewayMe if needed.

## Features
- Ethernet connectivity for internet access
- Mesh network coordinator
- Data aggregation from sensor nodes
- Cloud/server communication bridge
