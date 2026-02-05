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
#define NODE_ID "DAM01"
#define SENSOR_TYPE_ID 1
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define TRIG_PIN 5
#define ECHO_PIN 6

// --- State ---
// Removed lastReadTime

// Packed struct for binary transmission (3 bytes data + 1 byte type)
struct __attribute__((packed)) SensorPacket {
  uint8_t battery;
  uint16_t waterDist; // mm
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
}

uint16_t getDistdMM() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long dur = pulseIn(ECHO_PIN, HIGH, 30000);
  if (dur == 0) return 0; // Error
  
  // Speed of sound: 0.0343 cm/us -> 0.343 mm/us
  // dist = (dur * speed) / 2
  float dist_mm = (dur * 0.343f) / 2.0f;
  return (uint16_t)dist_mm;
}

void readSensors() {
  currentPacket.battery = 4; // Placeholder
  currentPacket.waterDist = getDistdMM();
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
