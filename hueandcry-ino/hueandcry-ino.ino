#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "hue_controller.h"
#include "hue_light.h"

const char* uid = "wZ3ic7KaZdUCTj5SOi8w82lwBSIPe-E30Y7374tJ";
const char* ssid = "Blackhawk East 2.4G";
const char* password = "fluffyteapot";
const char* defaultHost = "192.168.1.7";
WiFiClient wifiClient;
HueController hue(wifiClient, uid, defaultHost);
vector<HueLight> lights;

void setup() {
  Serial.begin(112500);
  delay(10);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected!");
  Serial.println("IP Address:");
  Serial.println(WiFi.localIP());

  hue.initialize();
  lights = hue.getGroupLights("Bill's Office");
}

void loop() {
  Serial.println("Office lights:");
  for (HueLight light : lights) {
    Serial.println("Light " + String(light.getId()));
    Serial.println("\t" + hue.getLightState(light));
  }
  Serial.println("HA!");
  delay(10000);
}
