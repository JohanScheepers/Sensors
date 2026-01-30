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
unsigned long lastReadTime = 0;
float maxWindCurrent = 0.0;  // Gust tracking

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  double rainfall;      // Running total mm since boot
  float windSpeed;
  float windGust;
  int windDirection;
};

SensorData currentData;

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
int getWindDirection() {
  int val = analogRead(WIND_DIR_PIN);
  // Simplified mapping for 0-360 degrees
  // In a real scenario, this would use a lookup table for a voltage divider
  return map(val, 0, 1023, 0, 359);
}

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  
  if (!bme.begin(0x76)) {
    UART_STREAM_PORT.println(F("{\"error\":\"BME280 not found\"}"));
  }
  
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  
  pinMode(RAIN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RAIN_PIN), onRainTip, FALLING);
  
  pinMode(WIND_SPEED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), onWindPulse, FALLING);
  
  pinMode(WIND_DIR_PIN, INPUT);
}

void readSensors() {
  currentData.temperature = bme.readTemperature();
  currentData.humidity = bme.readHumidity();
  currentData.pressure = bme.readPressure() / 100.0F;
  
  // Rainfall
  currentData.rainfall = rainTips * RAIN_TIP_MM;
  
  // Wind Speed (avg over interval)
  // freq = pulses / (interval / 1000)
  float freq = (float)windPulses / (SENSOR_READ_INTERVAL / 1000.0);
  currentData.windSpeed = freq * (WIND_SCALE / 3.6); // Convert km/h to m/s
  
  // Gust (simplified: peak during interval is harder without continuous sampling, 
  // but we'll use the interval avg and a "peak" pulse rate if we had a shorter window)
  // For now, we'll just simulate gust as a slightly higher random factor or peak pulse count
  currentData.windGust = currentData.windSpeed * 1.5; 
  
  currentData.windDirection = getWindDirection();
  
  // Reset counters for next interval
  windPulses = 0;
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.temperature;
  doc["h_pct"] = currentData.humidity;
  doc["p_hpa"] = currentData.pressure;
  doc["rain_mm"] = currentData.rainfall;
  doc["wind_ms"] = currentData.windSpeed;
  doc["windGust_ms"] = currentData.windGust;
  doc["windDirection_d"] = currentData.windDirection;
  
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
