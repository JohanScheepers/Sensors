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
#define NODE_ID "VAL01"
#define SENSOR_TYPE_ID 11
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define RELAY_PIN 10


// --- State ---
// Removed lastReadTime
bool valveOpen = false;

// Packed struct for binary transmission (6 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  uint8_t battery;
  uint8_t state; // 1 = open, 0 = closed
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void processCommands() {
  if (UART_STREAM_PORT.available()) {
    String cmd = UART_STREAM_PORT.readStringUntil('\n');
    cmd.trim(); cmd.toUpperCase();
    if (cmd == "OPEN") {
      valveOpen = true;
      digitalWrite(RELAY_PIN, HIGH);
    } else if (cmd == "CLOSE") {
      valveOpen = false;
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}

void readSensors() {
  currentPacket.battery = 4; // Placeholder
  currentPacket.state = valveOpen ? 1 : 0;
}

void transmitToMesh() {
  UART_STREAM_PORT.write((uint8_t)SENSOR_TYPE_ID);
  UART_STREAM_PORT.write((const uint8_t*)&currentPacket, sizeof(SensorPacket));
}

void loop() {
  processCommands();
  readSensors();
  transmitToMesh();
  delay(SENSOR_READ_INTERVAL);
}
