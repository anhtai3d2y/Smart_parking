#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <SocketIoClient.h> //version latest 0.3

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

void messageEvenetHandler(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
}

void setup() {
  USE_SERIAL.begin(115200);

  USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFiMulti.addAP("CHINH CHINH HY", "chinhchinhhy");

  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  webSocket.on("reply", messageEvenetHandler);
  webSocket.begin("192.168.1.9", 3030);
  // use HTTP Basic Authorization this is optional remove if not needed
  //webSocket.setAuthorization("username", "password");
}
uint64_t messageTimestamp;
void loop() {
  webSocket.loop();
  uint64_t now = millis();
  if (now - messageTimestamp > 6000) {
    messageTimestamp = now;
    // Send event
    webSocket.emit("message", "\"this is a message from the client\"");
  }
}
