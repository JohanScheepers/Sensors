#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

// --- Configuration ---
#define NODE_ID "MOI01"
#define SENSOR_TYPE "MoistureMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define MOISTURE_PIN A1
#define DRY_VAL 850
#define WET_VAL 400

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
unsigned long lastReadTime = 0;

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float moisture;
};

SensorData currentData;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(MOISTURE_PIN, INPUT);
}

float getMoisture() {
  int raw = analogRead(MOISTURE_PIN);
  float pct = map(raw, DRY_VAL, WET_VAL, 0, 100);
  return constrain(pct, 0.0f, 100.0f);
}

void readSensors() {
  currentData.temperature = bme.readTemperature();
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  currentData.moisture = getMoisture();
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.temperature;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["moi_pct"] = currentData.moisture;
  
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
