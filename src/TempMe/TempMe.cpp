#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

// --- Configuration ---
#define NODE_ID "TEMP01"
#define SENSOR_TYPE "TempMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000
#define SEALEVELPRESSURE_HPA (1013.25)

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
unsigned long lastReadTime = 0;

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float altitude;
};

SensorData currentData;

void setup() {
  UART_STREAM_PORT.begin(115200);
  while (!UART_STREAM_PORT);
  
  Wire.begin();
  
  if (!bme.begin(0x76)) {
    // Basic fallback for error reporting
    UART_STREAM_PORT.println(F("{\"error\":\"BME280 not found\"}"));
    while (1);
  }
  
  bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                  Adafruit_BME280::SAMPLING_X2,
                  Adafruit_BME280::SAMPLING_X16,
                  Adafruit_BME280::SAMPLING_X1,
                  Adafruit_BME280::FILTER_X16,
                  Adafruit_BME280::STANDBY_MS_500);
}

void readSensors() {
  currentData.temperature = bme.readTemperature(); // Already in Celsius
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  currentData.altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.temperature;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["alt_m"] = currentData.altitude;
  
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
