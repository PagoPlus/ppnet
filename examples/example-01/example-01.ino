#include <Arduino.h>
#include <PPNet.h>

#include <WiFi.h>

#define SOFTWARE_VERSION 0x00001
#define HARDWARE_REVISION 0x0003

PPNetwork::PPNet ppnet(&Serial1, PPNetwork::WriteTargetType::SUNTECH);

void setup()
{
  Serial.begin(115200);
  // We'll use Serial1 as our Suntech device
  Serial1.begin(9600);

  // start wifi so we have true random numbers
  WiFi.mode(WIFI_STA);
  WiFi.begin();

  // get our unique ID
  char ssid[64];
  snprintf(ssid, sizeof(ssid), "%llX", ESP.getEfuseMac());

  // Since we just booted, we send a HELLO message to the server
  ppnet.WriteMessage(PPNetwork::Message::HelloMessage {
    // our unique board ID
    .uniqueId = ssid,
    // the name of the board
    .boardIdentifier = "DemoBoard",
    // our current system version
    .version = SOFTWARE_VERSION,
    .boardVersion = HARDWARE_REVISION,
    .bootId = esp_random(),
  });
}

void loop()
{
  // send one fake message every 5 seconds
  ppnet.WriteMessage(PPNetwork::Message::SingleCounterMessage {
    .kind = "MIO/PEN",
    .value = 1,
    .pulses = 6,
    .duration_ms = 5000
  });

  delay(5000);
}