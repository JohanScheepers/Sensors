#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>
#include <SDI12.h>

// --- Configuration ---
#define NODE_ID "MOI01"
#define SENSOR_TYPE "MoistureMe"
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000 
#define SDI12_DATA_PIN 2  // Digital pin for SDI-12 data
#define SENSOR_ADDRESS '0' // Default SDI-12 address

// --- Hardware ---
Adafruit_BME280 bme;
SDI12 sdi12(SDI12_DATA_PIN);

// --- State ---
unsigned long lastReadTime = 0;

struct SensorData {
  float airTemp;
  float airHum;
  float airPres;
  float soilTemp[4]; // 4 Depths
  float moisture[4]; // 4 Depths
  bool sdiSuccess;
};

SensorData currentData;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  
  if (!bme.begin(0x76)) {
    UART_STREAM_PORT.println(F("{\"error\":\"BME280 not found\"}"));
  }
  
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  
  sdi12.begin();
  delay(500); // Power up stabilization
}

bool readSDI12() {
  String command = String(SENSOR_ADDRESS) + "M!"; 
  sdi12.sendCommand(command);
  
  // Wait for measurement to complete (max 10s)
  unsigned long start = millis();
  String response = "";
  while (millis() - start < 10000) {
    if (sdi12.available()) {
      char c = sdi12.read();
      if (c == '\n' || c == '\r') break;
      response += c;
    }
  }
  
  sdi12.clearBuffer();
  
  // Request data (D0!)
  command = String(SENSOR_ADDRESS) + "D0!";
  sdi12.sendCommand(command);
  
  start = millis();
  response = "";
  while (millis() - start < 5000) {
    if (sdi12.available()) {
      char c = sdi12.read();
      if (c == '\n' || c == '\r') break;
      response += c;
    }
  }

  // Parse SDI-12 response: addr+t1+m1+t2+m2+t3+m3+t4+m4 (Interleaved pairs)
  // format: 0+21.5+34.2+21.0+33.1+20.5+31.0+20.0+28.5 
  if (response.length() > 2) {
    int pos = 0;
    // Skip address (usually response[0])
    pos = response.indexOf('+', 0);
    if (pos == -1) pos = response.indexOf('-', 0);

    for (int i = 0; i < 4; i++) {
        // Read Temp
        if (pos != -1) {
            currentData.soilTemp[i] = response.substring(pos).toFloat();
            // Move to next value
            pos = response.indexOf('+', pos + 1);
            if (pos == -1) pos = response.indexOf('-', pos + 1);
        } else {
            currentData.soilTemp[i] = -99.0;
        }

        // Read Moisture
        if (pos != -1) {
            currentData.moisture[i] = response.substring(pos).toFloat();
            // Move to next value for next iteration
            pos = response.indexOf('+', pos + 1);
            if (pos == -1) pos = response.indexOf('-', pos + 1);
        } else {
            currentData.moisture[i] = -1.0;
        }
    }
    return true;
  }
  return false;
}

void readSensors() {
  currentData.airTemp = bme.readTemperature();
  currentData.airHum = bme.readHumidity();
  currentData.airPres = bme.readPressure() / 100.0F;
  currentData.sdiSuccess = readSDI12();
}

void transmitToMesh() {
  JsonDocument doc;
  doc["id"] = NODE_ID;
  doc["type"] = SENSOR_TYPE;
  doc["t_c"] = currentData.airTemp;
  doc["h_pct"] = currentData.airHum;
  doc["p_hpa"] = currentData.airPres;
  
  if (currentData.sdiSuccess) {
    JsonArray soil_t = doc["soil_t_c"].to<JsonArray>();
    JsonArray moisture = doc["moi_raw"].to<JsonArray>();
    for (int i = 0; i < 4; i++) {
      soil_t.add(currentData.soilTemp[i]);
      moisture.add(currentData.moisture[i]);
    }
  } else {
    doc["error"] = "SDI12_FAIL";
  }
  
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
