# Sensor

These are the sensors required for my IOT project.

## [GatewayMe](./GatewayMe)

This will be the main gateway for the mesh network. It will be connected to the internet via Ethernet and will act as a bridge between the mesh network and the internet.

## [TempMe](./TempMe)

Using a BME690 for VOCs, barometric pressure, humidity, and temperature in a single, compact package.

This will also act as the smallest device and acts as a repeater for the mesh network and the base for most of the other sensors. It will have a port where you can plug in other sensors. It will be battery powered.

## [TankMe](./TankMe)

This will be a TempMe, port populated with a water pressure level sensor(0-10m).

## [DamMe](./DamMe)

This will be a TempMe, port populated with a ultrasonic distance sensor.

## [TroughMe](./TroughMe)

This will be a TempMe, port populated with a water pressure level sensor (0-1.5m).

# [FridgeMe](./FridgeMe)

This will be a TempMe, port populated with external temperature sensor probe. And will be placed next to the fridge

## [RainMe](./RainMe)

This will be a TempMe, port populated with reed switch (used with a tipping bucket rain gauge, not included).

## [GateMe](./GateMe)

This will be a TempMe, port populated with magnetic contact switch.

## [SwitchMe](./SwitchMe)

This will be a TempMe, port will be TTL high/low GPIO.

## [ValveMe](./ValveMe)

This will be a TempMe, port will be 12VDC solenoid valve.

## [MoistureMe](./MoistureMe)

This will be a TempMe, port will be SI-12 port populated with a moisture sensor.

## [FenceMe](./FenceMe)

This will be a TempMe, port populated with a high voltage sensor (up 12kV). (https://github.com/kiu/lofence)


