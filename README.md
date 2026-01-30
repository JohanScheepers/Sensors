# IOT Sensor Network

A comprehensive suite of IOT sensor nodes designed for agricultural and industrial monitoring. Built on the **ARM (STM32)** architecture and utilizing **BME280** sensors, these nodes communicate via a meshed UART JSON protocol.

## System Architecture

All nodes (except the Gateway) share a common base architecture:
- **Environment**: Bosch BME280 (Temp, Humidity, Pressure)
- **Messaging**: Standardized JSON over UART (115200 baud)
- **Power**: Optimized for battery and low-power mesh operation

## Hardware Visuals

````carousel
```markdown
// Weather Station (RainMe)
![RainMe Weather Station](./src/RainMe/complete-weather-station-diy-kit-anemometer-wind-vane-rain-bucket-dht22.webp)
```
<!-- slide -->
```markdown
// Trough Monitor (TroughMe)
![TroughMe Controller](./src/TroughMe/trough_controller_1769778774982.png)
```
<!-- slide -->
```markdown
// Dam Monitor (DamMe)
![DamMe Controller](./src/DamMe/dam_controller_1769778753801.png)
```
<!-- slide -->
```markdown
// Fridge Monitor (FridgeMe)
![FridgeMe Controller](./src/FridgeMe/fridge_controller_1769778820964.png)
```
<!-- slide -->
```markdown
// Water Level Monitor (TankMe)
![TankMe Controller](./src/TankMe/tank_controller.png)
```
<!-- slide -->
```markdown
// Mesh Gateway (GatewayMe)
![GatewayMe Controller](./GatewayMe/gateway_controller.png)
```
````

## Sensor Catalog

### [GatewayMe](./GatewayMe)
The primary bridge between the local mesh network and the internet via Ethernet.

### [TempMe](./src/TempMe)
The base environmental node and mesh repeater. Measures temperature, humidity, pressure, and altitude.

### [TankMe](./src/TankMe)
Monitors water levels in large tanks (0-10m) using hydrostatic pressure sensing.

### [DamMe](./src/DamMe)
Non-contact water level monitoring for dams and open water using ultrasonic ranging.

### [TroughMe](./src/TroughMe)
Precision low-range monitoring (0-1.5m) for livestock drinking troughs.

### [FridgeMe](./src/FridgeMe)
Dual-zone monitoring for cold storage, featuring an external temperature probe.

### [RainMe](./src/RainMe)
Weather station node monitoring rainfall, wind speed/gust, and wind direction.

### [GateMe](./src/GateMe)
Real-time security and operational status for gates and doors.

### [SwitchMe](./src/SwitchMe)
Remote-controlled logic output for activating external equipment.

### [ValveMe](./src/ValveMe)
Automated flow control for 12VDC solenoid valves.

### [MoistureMe](./src/MoistureMe)
Professional SDI-12 soil monitor for multi-depth moisture and temperature profiling.

### [FenceMe](./src/FenceMe)
Safety-critical monitoring for electric fences up to 12kV.

---
*Developed with PlatformIO for professional ARM-based embedded development.*
