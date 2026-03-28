#include "Arduino.h"
#include <esp_wifi.h>
#include "LoRaWan_APP.h"
#include <Preferences.h>

/* ---------- TTN KEYS (OTAA) ---------- */
uint8_t devEui[] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x07, 0x5E, 0xC9 };
uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
uint8_t appKey[] = { 0xFB, 0x2D, 0xE5, 0x63, 0x5D, 0x5B, 0x68, 0xA9, 0xFA, 0x8D, 0xE2, 0x1B, 0xB0, 0x94, 0xB2, 0x45 };

/* ---------- MANDATORY ABP KEYS (Required by Linker even for OTAA) ---------- */
uint32_t devAddr = ( uint32_t )0x007e0013;
uint8_t nwkSKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appSKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* ---------- LORA SETTINGS ---------- */
bool overTheAirActivation = true;
DeviceClass_t loraWanClass = CLASS_A;
bool loraWanAdr = true;
bool isTxConfirmed = false;
uint8_t appPort = 2; 
uint32_t appTxDutyCycle = 15000;
uint8_t confirmedNbTrials = 4; // Added this back - missing in previous version
uint16_t userChannelsMask[6] = { 0x00FF, 0, 0, 0, 0, 0 };

/* ---------- DYNAMIC SETTINGS ---------- */
int8_t current_rssi_limit = -100; 
uint32_t current_heartbeat_ms = 300000; 
const int deskFilter = -20;
const unsigned long uplinkCooldown = 60000; 
const unsigned long forgetDeviceInterval = 86400000; // 24 Hours

/* ---------- WHITELIST ---------- */
String knownDevices[] = { 
  "32:a9:c5:ca:74:b1", 
  "9c:a9:c5:cd:6f:2c" 
};
int whitelistSize = 2;

#define MAX_DEVICES 20
uint16_t detectedDevices[MAX_DEVICES];
unsigned long deviceLastSeen[MAX_DEVICES];
int deviceCount = 0;

/* ---------- GLOBALS ---------- */
Preferences prefs;
unsigned long lastUplink = 0;
unsigned long lastHeartbeat = 0;
bool intruderDetected = false;
int intruderRSSI = -120;
uint16_t intruderHash = 0;

/* ---------- DISTANCE LOGIC ---------- */
uint16_t estimateDistance(int rssi) {
  if (rssi >= -30) return 2; 
  float measuredPower = -45.0; 
  float n = 2.7;               
  float distance = pow(10, (measuredPower - rssi) / (10 * n));
  return (uint16_t)distance;
}

/* ---------- DOWNLINK HANDLER ---------- */
void downLinkDataHandle(McpsIndication_t *mcpsIndication) {
  if (mcpsIndication->RxData && mcpsIndication->Port == 2) {
    int8_t rawRssi = (int8_t)mcpsIndication->Buffer[0];
    int8_t newLimit = (rawRssi > 0) ? (rawRssi * -1) : rawRssi;

    if (newLimit >= -110 && newLimit <= -30) {
      current_rssi_limit = newLimit;
      prefs.begin("farmhouse", false);
      prefs.putChar("rssi_limit", current_rssi_limit);
      prefs.end();
    }

    if (mcpsIndication->BufferSize >= 2) {
       uint8_t mins = mcpsIndication->Buffer[1];
       if (mins >= 1 && mins <= 60) {
          current_heartbeat_ms = (uint32_t)mins * 60000;
          prefs.begin("farmhouse", false);
          prefs.putUInt("hbeat_ms", current_heartbeat_ms);
          prefs.end();
       }
    }
  }
}

/* ---------- BATTERY UTILITY ---------- */
float getBatteryVoltage() {
  digitalWrite(37, HIGH); delay(50); 
  uint32_t sum = 0;
  for(int i=0; i<10; i++) { sum += analogReadMilliVolts(1); delay(2); }
  float pin_mv = sum / 10.0;
  float battery_v = (pin_mv * 4.988) / 1000.0; 
  digitalWrite(37, LOW); 
  return (battery_v > 2.0) ? battery_v : 0.0; 
}

/* ---------- UPLINK PREPARATION ---------- */
void prepareTxFrame(uint8_t port) {
  float vbat = getBatteryVoltage();
  uint16_t batt_payload = (uint16_t)(vbat * 1000);
  int percent = (int)((vbat - 3.2) / (4.2 - 3.2) * 100);
  if(percent > 100) percent = 100;
  if(percent < 0) percent = 0;

  uint16_t meters = estimateDistance(intruderRSSI);

  appDataSize = 10;
  appData[0] = intruderDetected ? 1 : 0;
  appData[1] = (uint8_t)(batt_payload >> 8);
  appData[2] = (uint8_t)(batt_payload & 0xFF);
  appData[3] = (uint8_t)percent;
  appData[4] = (uint8_t)abs(intruderRSSI);
  appData[5] = (uint8_t)(intruderHash >> 8);
  appData[6] = (uint8_t)(intruderHash & 0xFF);
  appData[7] = (uint8_t)abs(current_rssi_limit); 
  appData[8] = (uint8_t)(meters >> 8); 
  appData[9] = (uint8_t)(meters & 0xFF);
}

/* ---------- UTILITIES ---------- */
uint16_t macHash(const char* mac) {
  uint16_t hash = 0;
  for(int i=0; mac[i] != 0; i++) hash = hash * 31 + mac[i];
  return hash;
}

bool isKnownRecently(uint16_t hash) {
  for(int i=0; i<deviceCount; i++) { 
    if(detectedDevices[i] == hash) {
      if(millis() - deviceLastSeen[i] < forgetDeviceInterval) return true;
      return false; 
    } 
  }
  return false;
}

void rememberDevice(uint16_t hash) {
  for(int i=0; i<deviceCount; i++) {
    if(detectedDevices[i] == hash) {
      deviceLastSeen[i] = millis();
      return;
    }
  }
  if(deviceCount < MAX_DEVICES) { 
    detectedDevices[deviceCount] = hash; 
    deviceLastSeen[deviceCount] = millis();
    deviceCount++;
  }
}

/* ---------- SNIFFER ---------- */
void sniffer(void* buf, wifi_promiscuous_pkt_type_t type) {
  if(type != WIFI_PKT_MGMT) return;
  const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
  if(pkt->payload[0] == 0x40) { 
    int rssi = pkt->rx_ctrl.rssi;
    if(rssi > deskFilter || rssi < current_rssi_limit) return;
    
    char macStr[18];
    sprintf(macStr,"%02x:%02x:%02x:%02x:%02x:%02x", 
            pkt->payload[10], pkt->payload[11], pkt->payload[12], 
            pkt->payload[13], pkt->payload[14], pkt->payload[15]);
    
    String detectedMac = String(macStr);
    for(int i=0; i<whitelistSize; i++) { 
      if(detectedMac.equalsIgnoreCase(knownDevices[i])) return; 
    }
    
    uint16_t hash = macHash(macStr);
    if(isKnownRecently(hash)) return;
    
    rememberDevice(hash);
    intruderDetected = true;
    intruderRSSI = rssi;
    intruderHash = hash;
  }
}

/* ---------- SETUP & LOOP ---------- */
void setup() {
  Serial.begin(115200);
  prefs.begin("farmhouse", true);
  current_rssi_limit = prefs.getChar("rssi_limit", -100); 
  current_heartbeat_ms = prefs.getUInt("hbeat_ms", 300000);
  prefs.end();

  pinMode(37, OUTPUT); digitalWrite(37, HIGH); 
  pinMode(21, OUTPUT); digitalWrite(21, LOW); 

  Mcu.begin(21, 0); 
  
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_mode(WIFI_MODE_NULL);
  esp_wifi_start();
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&sniffer);
  
  deviceState = DEVICE_STATE_INIT;
}

void loop() {
  switch(deviceState) {
    case DEVICE_STATE_INIT: 
      LoRaWAN.init(CLASS_A, (LoRaMacRegion_t)5); 
      deviceState = DEVICE_STATE_JOIN; break;
    case DEVICE_STATE_JOIN: 
      LoRaWAN.join(); break;
    case DEVICE_STATE_SEND:
      if((intruderDetected && (millis() - lastUplink > uplinkCooldown)) || (millis() - lastHeartbeat > current_heartbeat_ms)) {
        prepareTxFrame(appPort);
        LoRaWAN.send();
        lastUplink = millis();
        lastHeartbeat = millis();
        intruderDetected = false;
      }
      deviceState = DEVICE_STATE_CYCLE; break;
    case DEVICE_STATE_CYCLE: 
      txDutyCycleTime = 1000; 
      LoRaWAN.cycle(txDutyCycleTime); 
      deviceState = DEVICE_STATE_SLEEP; break;
    case DEVICE_STATE_SLEEP: 
      LoRaWAN.sleep(CLASS_A); break;
    default: 
      deviceState = DEVICE_STATE_INIT; break;
  }
}
