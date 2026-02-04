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
#define NODE_ID "TRO01"
#define SENSOR_TYPE_ID 10
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define PRESSURE_PIN A0
#define PRESSURE_VCC 5.0
#define PRESSURE_RANGE_KPA 15.0


// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
// Removed lastReadTime

// Packed struct for binary transmission (7 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  int8_t airTemp;
  uint8_t airHum;
  uint16_t airPres;
  uint8_t battery;
  uint16_t waterLevel; // mm
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(PRESSURE_PIN, INPUT);
}

uint16_t getWaterLevelMM() {
  float voltage = (analogRead(PRESSURE_PIN) / 1023.0) * PRESSURE_VCC;
  // Pressure (kPa)
  float pressure = ((voltage - 0.5) / 4.0) * PRESSURE_RANGE_KPA;
  // Pascals = kPa * 1000. 
  // P = rho * g * h => h = P / (rho * g)
  // h(m) = pressure(kPa) * 1000 / (1000 kg/m3 * 9.8 m/s2)
  // h(mm) = pressure(kPa) * 1000 * 1000 / 9800 ~= pressure * 102
  float height_m = max(0.0f, pressure / 9.8f);
  return (uint16_t)(height_m * 1000);
}

void readSensors() {
  currentPacket.airTemp = (int8_t)bme.readTemperature();
  currentPacket.airHum = (uint8_t)bme.readHumidity();
  currentPacket.airPres = (uint16_t)(bme.readPressure() / 100.0F);
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
