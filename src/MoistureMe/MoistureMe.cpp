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
#include <SDI12.h>

// --- Configuration ---
#define NODE_ID "MOI01"
#define SENSOR_TYPE_ID 6 
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define SDI12_DATA_PIN 2  // Digital pin for SDI-12 data
#define SENSOR_ADDRESS '0' // Default SDI-12 address

// --- Hardware ---
Adafruit_BME280 bme;
SDI12 sdi12(SDI12_DATA_PIN);

// --- State ---
// Removed lastReadTime

// Packed struct for binary transmission (13 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  int8_t airTemp;
  uint8_t airHum;
  uint16_t airPres;
  uint8_t battery;
  int8_t soilTemp[4];     // 4 Depths
  uint8_t moisture[4];     // 4 Depths
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  
  if (!bme.begin(0x76)) {
    // Error handling? For now, we assume hardware is present or we send 0s
  }
  
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  
  sdi12.begin();
  delay(500); // Power up stabilization
}

bool readSDI12() {
  String command = String(SENSOR_ADDRESS) + "M!"; 
  sdi12.sendCommand(command);
  
  // Wait for measurement to complete (max 10s)
  unsigned long start = millis();
  while (millis() - start < 10000) {
    if (sdi12.available()) {
      char c = sdi12.read();
      if (c == '\n' || c == '\r') break;
    }
  }
  
  sdi12.clearBuffer();
  
  // Request data (D0!)
  command = String(SENSOR_ADDRESS) + "D0!";
  sdi12.sendCommand(command);
  
  start = millis();
  String response = "";
  while (millis() - start < 5000) {
    if (sdi12.available()) {
      char c = sdi12.read();
      if (c == '\n' || c == '\r') break;
      response += c;
    }
  }

  // Parse SDI-12 response: addr+t1+m1+t2+m2+t3+m3+t4+m4
  // We need to parse floats and convert to our storage format
  if (response.length() > 2) {
    int pos = 0;
    // Skip address
    pos = response.indexOf('+', 0);
    if (pos == -1) pos = response.indexOf('-', 0);

    for (int i = 0; i < 4; i++) {
        // Read Temp
        if (pos != -1) {
            float t = response.substring(pos).toFloat();
            currentPacket.soilTemp[i] = (int8_t)t; 
            // Move to next
            pos = response.indexOf('+', pos + 1);
            if (pos == -1) pos = response.indexOf('-', pos + 1);
        } else {
            currentPacket.soilTemp[i] = -99;
        }

        // Read Moisture
        if (pos != -1) {
            float m = response.substring(pos).toFloat();
            currentPacket.moisture[i] = (uint8_t)m; // Assuming 0-100 range
            // Move to next
            pos = response.indexOf('+', pos + 1);
            if (pos == -1) pos = response.indexOf('-', pos + 1);
        } else {
            currentPacket.moisture[i] = 0;
        }
    }
    return true;
  }
  return false;
}

void readSensors() {
  currentPacket.airTemp = (int8_t)bme.readTemperature();
  currentPacket.airHum = (uint8_t)bme.readHumidity();
  currentPacket.airPres = (uint16_t)(bme.readPressure() / 100.0F);
  currentPacket.battery = 4; // Placeholder
  
  if (!readSDI12()) {
      // Fill with error values if SDI-12 fails
      for(int i=0; i<4; i++) {
          currentPacket.soilTemp[i] = -99;
          currentPacket.moisture[i] = 0;
      }
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
