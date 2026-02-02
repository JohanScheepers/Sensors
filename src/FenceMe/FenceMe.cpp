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
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// --- Configuration ---
#define NODE_ID "FEN01"
#define SENSOR_TYPE_ID 2
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 10000 
#define FENCE_PIN A2
#define ALERT_LED_PIN 12
#define VOLTAGE_THRESHOLD 3.0 // Low voltage alert threshold in kV

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
// Removed lastReadTime

// Packed struct for binary transmission (6 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  int8_t airTemp;
  uint8_t airHum;
  uint16_t airPres;
  uint16_t voltage; // kV * 100
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(FENCE_PIN, INPUT);
  pinMode(ALERT_LED_PIN, OUTPUT);
  digitalWrite(ALERT_LED_PIN, LOW);
}

float getVoltageKV() {
  // Scaling according to documentation/hardware isolation
  // original: (analogRead(FENCE_PIN) / 1023.0f) * 5.0f * 2.0f; 
  return (analogRead(FENCE_PIN) / 1023.0f) * 10.0f; 
}

void readSensors() {
  currentPacket.airTemp = (int8_t)bme.readTemperature();
  currentPacket.airHum = (uint8_t)bme.readHumidity();
  currentPacket.airPres = (uint16_t)(bme.readPressure() / 100.0F);
  
  float kv = getVoltageKV();
  currentPacket.voltage = (uint16_t)(kv * 100);
  
  // Update local alert LED
  if (kv < VOLTAGE_THRESHOLD) {
    digitalWrite(ALERT_LED_PIN, HIGH); // Alert ON
  } else {
    digitalWrite(ALERT_LED_PIN, LOW);  // Alert OFF
  }
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
