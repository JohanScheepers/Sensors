#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

// --- Configuration ---
#define NODE_ID "SWI01"
#define SENSOR_TYPE "SwitchMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define SWITCH_PIN 8
#define LED_PIN 9

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
unsigned long lastReadTime = 0;
bool switchState = false;

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  bool state;
};

SensorData currentData;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(SWITCH_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(SWITCH_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void processCommands() {
  if (UART_STREAM_PORT.available()) {
    String cmd = UART_STREAM_PORT.readStringUntil('\n');
    cmd.trim(); cmd.toUpperCase();
    if (cmd == "ON") {
      switchState = true;
      digitalWrite(SWITCH_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
    } else if (cmd == "OFF") {
      switchState = false;
      digitalWrite(SWITCH_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }
  }
}

void readSensors() {
  currentData.temperature = bme.readTemperature();
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  currentData.state = switchState;
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.temperature;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["on"] = currentData.state;
  
  serializeJson(doc, UART_STREAM_PORT);
  UART_STREAM_PORT.println();
}

void loop() {
  unsigned long currentTime = millis();
  processCommands();
  if (currentTime - lastReadTime >= SENSOR_READ_INTERVAL) {
    readSensors();
    transmitToMesh();
    lastReadTime = currentTime;
  }
  delay(100);
}
