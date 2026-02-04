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
#include <TinyGPS++.h>

// --- Configuration ---
#define NODE_ID "PIV01"
#define SENSOR_TYPE_ID 14
#define UART_STREAM_PORT Serial
#define GPS_SERIAL Serial1
#define SENSOR_READ_INTERVAL 60000 
#define PRESSURE_PIN A4
#define FLOW_PIN 2

// --- Hardware ---
Adafruit_BME280 bme;
TinyGPSPlus gps;

// --- State ---
volatile uint32_t flowPulses = 0;

// Packed struct for binary transmission (26 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  int8_t airTemp;
  uint8_t airHum;
  uint16_t airPres;
  uint8_t battery;
  int32_t lat;
  int32_t lon;
  uint16_t course;
  uint8_t speed;
  uint8_t hdop;
  uint8_t sat;
  uint16_t altitude;
  uint16_t waterPressure; // kPa * 10
  uint32_t flowTotal;     // L
};

SensorPacket currentPacket;

void IRAM_ATTR onFlowPulse() {
  flowPulses++;
}

void setup() {
  UART_STREAM_PORT.begin(115200);
  GPS_SERIAL.begin(9600);
  Wire.begin();
  if (!bme.begin(0x76)) {
      // Basic fallback
  }
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  
  pinMode(PRESSURE_PIN, INPUT);
  pinMode(FLOW_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_PIN), onFlowPulse, FALLING);
}

void readGPS() {
  while (GPS_SERIAL.available() > 0) {
    gps.encode(GPS_SERIAL.read());
  }
  if (gps.location.isValid()) {
    currentPacket.lat = (int32_t)(gps.location.lat() * 1000000);
    currentPacket.lon = (int32_t)(gps.location.lng() * 1000000);
  } else {
    currentPacket.lat = 0;
    currentPacket.lon = 0;
  }
  currentPacket.course = (uint16_t)gps.course.deg();
  currentPacket.speed = (uint8_t)gps.speed.kmph();
  currentPacket.hdop = (uint8_t)gps.hdop.value();
  currentPacket.sat = (uint8_t)gps.satellites.value();
  currentPacket.altitude = (uint16_t)gps.altitude.meters();
}

void readSensors() {
  currentPacket.airTemp = (int8_t)bme.readTemperature();
  currentPacket.airHum = (uint8_t)bme.readHumidity();
  currentPacket.airPres = (uint16_t)(bme.readPressure() / 100.0F);
  currentPacket.battery = 4; // Placeholder
  
  readGPS();
  
  // Pressure (scaled)
  float p_raw = analogRead(PRESSURE_PIN);
  currentPacket.waterPressure = (uint16_t)((p_raw / 1023.0f) * 1000.0f); // dummy scaling
  
  // Flow
  currentPacket.flowTotal = flowPulses; // simplified
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
