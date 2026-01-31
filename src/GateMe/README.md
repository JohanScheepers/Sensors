# GateMe - Gate & Door Status Monitor

A security and operational node for tracking the state of gates, doors, or windows.

## Overview
GateMe utilizes a magnetic contact switch to determine if a gate is open or closed. It tracks the duration of open states and provides real-time alerts for state changes.

## Hardware Specifications
- **MCU**: ARM
- **Environment Sensor**: BME280 (I2C 0x76)
- **Contact Sensor**: Magnetic Reed Switch / Hall Effect
- **Interface**: Pin **GPIO 7** (Internal Pull-up)

## Binary Data Payload

**Sensor Type ID:** 4

| Byte 1 | Byte 2 | Byte 3 | Byte 4-5 | Byte 6 |
|---|---|---|---|---|
| Type (4) | Air Temp (int8) | Humidity (uint8) | Pressure (uint16) | Gate Open (1=True)|

## Features
- **State Change Detection**: Immediate JSON broadcast upon gate opening/closing.
- **Duration Tracking**: Reports how long (in seconds) the gate has been in its current state.
- **Extended Open Alert**: Logic included to flag gates left open longer than a threshold (default 5 min).
- **Environment Context**: Useful for monitoring perimeter gates or barn doors where temp/humidity impacts livestock.
