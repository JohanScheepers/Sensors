#include <Arduino.h>NODE_ID
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

// --- Configuration ---
#define NODE_ID "FEN01"
#define SENSOR_TYPE "FenceMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 10000 
#define FENCE_PIN A2

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
unsigned long lastReadTime = 0;

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float voltage;
};

SensorData currentData;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(FENCE_PIN, INPUT);
}

float getVoltage() {
  return (analogRead(FENCE_PIN) / 1023.0f) * 5.0f * 2.0f; 
}

void readSensors() {
  currentData.temperature = bme.readTemperature();
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  currentData.voltage = getVoltage();
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = ;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.temperature;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["fen_kv"] = currentData.voltage;
  
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
