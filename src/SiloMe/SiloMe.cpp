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
#define NODE_ID "SIL01"
#define SENSOR_TYPE_ID 12
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define TRIG_PIN 5
#define ECHO_PIN 6


// --- State ---

// Packed struct for binary transmission (7 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  uint8_t battery;
  uint16_t level; // mm
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

uint16_t getDistanceMM() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long dur = pulseIn(ECHO_PIN, HIGH, 30000);
  if (dur == 0) return 0;
  float dist = (dur * 0.343f) / 2.0f;
  return (uint16_t)dist;
}

void readSensors() {
  currentPacket.battery = 4; // Placeholder
  currentPacket.level = getDistanceMM();
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
