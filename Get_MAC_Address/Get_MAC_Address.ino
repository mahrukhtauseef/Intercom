#include "WiFi.h"
#include "esp_wifi.h"

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("Getting MAC address using low-level API...");
  WiFi.mode(WIFI_STA);  // Set to station mode

  uint8_t mac[6];
  esp_wifi_get_mac(WIFI_IF_STA, mac);  // Get STA MAC address

  Serial.printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                mac[0], mac[1], mac[2],
                mac[3], mac[4], mac[5]);
}

void loop() {
}