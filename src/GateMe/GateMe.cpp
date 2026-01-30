#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

// --- Configuration ---
#define NODE_ID "GAT01"
#define SENSOR_TYPE "GateMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 10000 
#define GATE_PIN 7

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
unsigned long lastReadTime = 0;
bool lastGateState = false;
unsigned long gateOpenTime = 0;

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  bool gateOpen;
  unsigned long duration;
};

SensorData currentData;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(GATE_PIN, INPUT_PULLUP);
}

void readSensors() {
  currentData.temperature = bme.readTemperature();
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  currentData.gateOpen = digitalRead(GATE_PIN) == HIGH;
  
  if (currentData.gateOpen && !lastGateState) gateOpenTime = millis();
  currentData.duration = currentData.gateOpen ? (millis() - gateOpenTime) / 1000 : 0;
  lastGateState = currentData.gateOpen;
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.temperature;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["open"] = currentData.gateOpen;
  doc["dur_s"] = currentData.duration;
  
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
