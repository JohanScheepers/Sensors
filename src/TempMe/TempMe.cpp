#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// --- Configuration ---
#define NODE_ID "TEMP01"
#define SENSOR_TYPE_ID 0
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 60000
#define SEALEVELPRESSURE_HPA (1013.25)

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
// Removed lastReadTime

// Packed struct for binary transmission (6 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  int8_t airTemp;
  uint8_t airHum;
  uint16_t airPres;
  int16_t altitude; 
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  while (!UART_STREAM_PORT);
  
  Wire.begin();
  
  if (!bme.begin(0x76)) {
    // Basic fallback
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
  currentPacket.airTemp = (int8_t)bme.readTemperature();
  currentPacket.airHum = (uint8_t)bme.readHumidity();
  currentPacket.airPres = (uint16_t)(bme.readPressure() / 100.0F);
  currentPacket.altitude = (int16_t)bme.readAltitude(SEALEVELPRESSURE_HPA);
}

void transmitToMesh() {
  UART_STREAM_PORT.write((uint8_t)SENSOR_TYPE_ID);
  UART_STREAM_PORT.write((const uint8_t*)&currentPacket, sizeof(SensorPacket));
}

void loop() {
  readSensors();
  transmitToMesh();
  delay(SENSOR_READ_INTERVAL);
}
