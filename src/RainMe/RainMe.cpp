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
#define NODE_ID "RAI01"
#define SENSOR_TYPE_ID 7
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 

// Pin Mapping
#define RAIN_PIN 3           // Tipping bucket interrupt
#define WIND_SPEED_PIN 14    // Anemometer interrupt
#define WIND_DIR_PIN A3      // Wind vane analog input

// Constants
#define RAIN_TIP_MM 0.2794   // mm per tip
#define WIND_SCALE 2.4       // km/h per pulse/sec (example calibration)

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
volatile unsigned long rainTips = 0;
volatile unsigned long windPulses = 0;
unsigned long lastRainTipTime = 0;
unsigned long lastWindPulseTime = 0;

// Packed struct for binary transmission (11 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  int8_t airTemp;
  uint8_t airHum;
  uint16_t airPres;
  uint32_t rainTips;       // Total count to date
  uint8_t windSpeed;       // m/s
  uint8_t windGust;        // m/s
  uint8_t windDir;         // scaled 0-255 for 0-360 degrees
};

SensorPacket currentPacket;

// --- Interrupts ---
void IRAM_ATTR onRainTip() {
  unsigned long now = millis();
  if (now - lastRainTipTime > 100) {
    rainTips++;
    lastRainTipTime = now;
  }
}

void IRAM_ATTR onWindPulse() {
  unsigned long now = millis();
  if (now - lastWindPulseTime > 10) { // faster debounce for wind
    windPulses++;
    lastWindPulseTime = now;
  }
}

// --- Helpers ---
uint8_t getWindDirectionByte() {
  int val = analogRead(WIND_DIR_PIN);
  // Map 0-1023 (analog) to 0-255 (byte) representing 0-360 degrees
  return map(val, 0, 1023, 0, 255);
}

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  
  if (!bme.begin(0x76)) {
    // Error handling
  }
  
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  
  pinMode(RAIN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RAIN_PIN), onRainTip, FALLING);
  
  pinMode(WIND_SPEED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), onWindPulse, FALLING);
  
  pinMode(WIND_DIR_PIN, INPUT);
}

void readSensors() {
  float t = bme.readTemperature();
  currentPacket.airTemp = (int8_t)t;
  
  float h = bme.readHumidity();
  currentPacket.airHum = (uint8_t)h;
  
  float p = bme.readPressure() / 100.0F;
  currentPacket.airPres = (uint16_t)p;
  
  // Rainfall (Total Tips)
  currentPacket.rainTips = (uint32_t)rainTips;
  
  // Wind Speed (avg over interval)
  // freq = pulses / (interval / 1000)
  float freq = (float)windPulses / (SENSOR_READ_INTERVAL / 1000.0);
  float speed_ms = freq * (WIND_SCALE / 3.6); // Convert km/h to m/s
  currentPacket.windSpeed = (uint8_t)speed_ms;
  
  // Gust (simplified)
  float gust_ms = speed_ms * 1.5; 
  currentPacket.windGust = (uint8_t)gust_ms;
  
  currentPacket.windDir = getWindDirectionByte();
  
  // Reset counters for next interval (except rainTips, which is cumulative)
  windPulses = 0;
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
