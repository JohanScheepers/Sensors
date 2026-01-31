#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// --- Configuration ---
#define NODE_ID "GAT01"
#define SENSOR_TYPE_ID 4
#define UART_STREAM_PORT Serial
#define SENSOR_READ_INTERVAL 10000 
#define GATE_PIN 7

// --- Hardware ---
Adafruit_BME280 bme;

// --- State ---
bool lastGateState = false;
unsigned long gateOpenTime = 0;

// Packed struct for binary transmission (5 bytes data + 1 byte type sent separately)
struct __attribute__((packed)) SensorPacket {
  int8_t airTemp;
  uint8_t airHum;
  uint16_t airPres;
  uint8_t gateOpen; // 1 = open, 0 = closed
};

SensorPacket currentPacket;

void setup() {
  UART_STREAM_PORT.begin(115200);
  Wire.begin();
  if (!bme.begin(0x76)) while (1);
  bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X2, Adafruit_BME280::SAMPLING_X16, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_X16, Adafruit_BME280::STANDBY_MS_500);
  pinMode(GATE_PIN, INPUT_PULLUP);
}

void readSensors() {
  currentPacket.airTemp = (int8_t)bme.readTemperature();
  currentPacket.airHum = (uint8_t)bme.readHumidity();
  currentPacket.airPres = (uint16_t)(bme.readPressure() / 100.0F);
  currentPacket.gateOpen = (digitalRead(GATE_PIN) == HIGH) ? 1 : 0;
  
  // Logic tracking (local only usage or debug)
  bool isOpen = (currentPacket.gateOpen == 1);
  if (isOpen && !lastGateState) gateOpenTime = millis();
  lastGateState = isOpen;
}

void transmitToMesh() {
  UART_STREAM_PORT.write((uint8_t)SENSOR_TYPE_ID);
  UART_STREAM_PORT.write((const uint8_t*)&currentPacket, sizeof(SensorPacket));
}

void loop() {
}
