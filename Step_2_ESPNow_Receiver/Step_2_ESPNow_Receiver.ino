#include <esp_now.h>
#include <WiFi.h>

int LEDPin = 13;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  int receivedValue;
  memcpy(&receivedValue, incomingData, sizeof(receivedValue));
  int ledState = digitalRead(LEDPin);
  if (receivedValue == 1){
  if (ledState == HIGH) {
    digitalWrite(LEDPin,LOW);
    } else {
    digitalWrite(LEDPin, HIGH);
    }
  }
}

void setup() {
  // LED Pin
  pinMode(13, OUTPUT);

  // Initialize Serial Monitor
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  Serial.print("Ready to receive");
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
 
void loop() {

}