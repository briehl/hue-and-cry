#ifndef HUE_CONTROLLER_H
#define HUE_CONTROLLER_H

#include "Arduino.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "hue_light.h"
using std::vector;

class HueController
{
  public:
    HueController(WiFiClient& client, const char* username, const char* defaultHost);
    void initialize();
    void testLights();
    vector<HueLight> getGroupLights(const char* groupName);
    void updateLight(HueLight light);
    String getLightState(HueLight light);
    void updateLightState(HueLight light, String state);
    void fetchLightState(HueLight& light);
  private:
    enum RequestType { GET, POST, PUT, UPDATE, DELETE };
    String _getHueIp();
    DynamicJsonDocument _makeGetRequest(String path);
    DynamicJsonDocument _makePostRequest(String path, String body);
    DynamicJsonDocument _makeRequest(RequestType type, String path, String body);
    const char* _uid;
    char* _ip;
    char* _baseUrl;
    const char* _defaultHost;
    WiFiClient* _wifiClient;
};

#endif
