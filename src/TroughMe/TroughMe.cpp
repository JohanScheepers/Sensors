#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

// --- Configuration ---
#define NODE_ID "TRO01"
#define SENSOR_TYPE "TroughMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define PRESSURE_PIN A0
#define PRESSURE_VCC 5.0
#define PRESSURE_RANGE_KPA 15.0


// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
unsigned long lastReadTime = 0;

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float waterLevel;
};

SensorData currentData;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(PRESSURE_PIN, INPUT);
}

float getWaterLevel() {
  float voltage = (analogRead(PRESSURE_PIN) / 1023.0) * PRESSURE_VCC;
  float pressure = ((voltage - 0.5) / 4.0) * PRESSURE_RANGE_KPA;
  return max(0.0f, pressure / 9.8f);
}

void readSensors() {
  currentData.temperature = bme.readTemperature();
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  currentData.waterLevel = getWaterLevel();
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.temperature;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["lvl_m"] = currentData.waterLevel;
  
  serializeJson(doc, UART_STREAM_PORT);
  UART_STREAM_PORT.println();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastReadTime >= SENSOR_READ_INTERVAL) {
    readSensors();
    transmitToMesh();
    lastReadTime = currentTime;
  }
  delay(100);
}
