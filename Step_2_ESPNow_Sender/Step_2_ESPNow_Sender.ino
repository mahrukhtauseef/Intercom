#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xAC, 0x67, 0xB2, 0x36, 0xCE, 0xD4};

//Button pin
int buttonPin = 13; 

//Previous state of the buttono
int lastButtonState = 0;

//Adding delay to debounce the light flicker.
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // milliseconds


esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  //Declaring pin as input
  pinMode(buttonPin, INPUT);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
  int send = 0;
  int currentButtonState = digitalRead(buttonPin);

  if (currentButtonState != lastButtonState){
    lastDebounceTime = millis();
  }

    if (currentButtonState==1 && lastButtonState==0){
  // Send message via ESP-NOW
      send = 1;
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send, sizeof(send));
      if (result == ESP_OK) {
        Serial.println("Sent with success");
      }
      else {
        Serial.println("Error sending the data");
      }
  }
  lastButtonState = currentButtonState;
}
 