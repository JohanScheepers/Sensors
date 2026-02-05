/*
 *Copyright(c) 2025 Signal - Owl PTY LTD
 *
 * All Rights Reserved.
 *
 * Unauthorized copying of this file,
 * via any medium is strictly prohibited.Proprietary and confidential.
 */

#include <Arduino.h>
#include <Wire.h>

// --- Configuration ---
#define NODE_ID "TNK01"
#define SENSOR_TYPE_ID 9
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define PRESSURE_PIN A0
#define PRESSURE_VCC 5.0
#define PRESSURE_RANGE_KPA 100.0


// --- State ---
// Removed lastReadTime

// Packed struct for binary transmission (7 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  uint8_t battery;
  uint16_t waterLevel; // mm
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  pinMode(PRESSURE_PIN, INPUT);
}

uint16_t getWaterLevelMM() {
  float voltage = (analogRead(PRESSURE_PIN) / 1023.0) * PRESSURE_VCC;
  // KPa
  float pressure = ((voltage - 0.5) / 4.0) * PRESSURE_RANGE_KPA;
  // h(m) = pressure / 9.8
  float height_m = max(0.0f, pressure / 9.8f);
  return (uint16_t)(height_m * 1000);
}

void readSensors() {
  currentPacket.battery = 4; // Placeholder
  currentPacket.waterLevel = getWaterLevelMM();
}

void transmitToMesh() {
  UART_STREAM_PORT.write((uint8_t)SENSOR_TYPE_ID);
  UART_STREAM_PORT.write((const uint8_t*)&currentPacket, sizeof(SensorPacket));
}

void loop() {
  readSensors();
  transmitToMesh();
  delay(SENSOR_READ_INTERVAL);
}
