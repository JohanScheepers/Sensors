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
#define NODE_ID "SWI01"
#define SENSOR_TYPE_ID 8
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define SWITCH_PIN 8
#define LED_PIN 9

// --- State ---
// Removed lastReadTime
bool switchState = false;

// Packed struct for binary transmission (6 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  uint8_t battery;
  uint8_t state; // 1 = on, 0 = off
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  pinMode(SWITCH_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(SWITCH_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void processCommands() {
  if (UART_STREAM_PORT.available()) {
    String cmd = UART_STREAM_PORT.readStringUntil('\n');
    cmd.trim(); cmd.toUpperCase();
    if (cmd == "ON") {
      switchState = true;
      digitalWrite(SWITCH_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
    } else if (cmd == "OFF") {
      switchState = false;
      digitalWrite(SWITCH_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }
  }
}

void readSensors() {
  currentPacket.battery = 4; // Placeholder
  currentPacket.state = switchState ? 1 : 0;
}

void transmitToMesh() {
  UART_STREAM_PORT.write((uint8_t)SENSOR_TYPE_ID);
  UART_STREAM_PORT.write((const uint8_t*)&currentPacket, sizeof(SensorPacket));
}

void loop() {
  processCommands(); // Process any pending commands before sleeping
  readSensors();
  transmitToMesh();
  delay(SENSOR_READ_INTERVAL);
}
