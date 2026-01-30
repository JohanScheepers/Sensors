#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// --- Configuration ---
#define NODE_ID "FRI01"
#define SENSOR_TYPE "FridgeMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define ONE_WIRE_BUS 4

// --- Hardware ---
Adafruit_BME280 bme;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20(&oneWire);

// --- State ---
unsigned long lastReadTime = 0;

struct SensorData {
  float ambientTemp;
  float humidity;
  float pressure;
  float probeTemp;
};

SensorData currentData;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  ds18b20.begin();
}

void readSensors() {
  currentData.ambientTemp = bme.readTemperature();
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  ds18b20.requestTemperatures();
  currentData.probeTemp = ds18b20.getTempCByIndex(0); // getTempC returns Celsius
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["amb_t_c"] = currentData.ambientTemp;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["probe_t_c"] = currentData.probeTemp;
  
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
