#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

// --- Configuration ---
#define NODE_ID "RAI01"
#define SENSOR_TYPE "RainMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define REED_PIN 3
#define TIP_ML 0.2794

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
volatile unsigned long tips = 0;
unsigned long lastReadTime = 0;
unsigned long lastTipTime = 0;

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float rainfall;
};

SensorData currentData;

void IRAM_ATTR onTip() {
  if (millis() - lastTipTime > 100) {
    tips++;
    lastTipTime = millis();
  }
}

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(REED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REED_PIN), onTip, FALLING);
}

void readSensors() {
  currentData.temperature = bme.readTemperature();
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  currentData.rainfall = tips * TIP_ML;
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.temperature;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["rain_mm"] = currentData.rainfall;
  
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
