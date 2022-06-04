#include "hue_controller.h"

#define DEFAULT_IP "192.168.1.7"
#include <WiFiClientSecureBearSSL.h>

HueController::HueController(WiFiClient& wifiClient, const char* username, const char* defaultHost) {
  _wifiClient = &wifiClient;
  _defaultHost = defaultHost;
  _uid = username;
}

void HueController::initialize() {
  String ipStr = _getHueIp();
  int ipStrLen = ipStr.length() + 1;
  _ip = new char [ipStrLen];
  ipStr.toCharArray(_ip, ipStrLen);
  int baseUrlLen = strlen(_uid) + ipStrLen + 16;
  _baseUrl = new char [baseUrlLen];
  snprintf(_baseUrl, baseUrlLen, "http://%s/api/%s/", _ip, _uid);
  Serial.print("Hue IP: ");
  Serial.println(_ip);
  Serial.print("Base Controller URL: ");
  Serial.println(_baseUrl);
}

String HueController::_getHueIp() {
  BearSSL::WiFiClientSecure secureWifi;
  secureWifi.setInsecure();
  HTTPClient http;
  http.begin(secureWifi, "https://discovery.meethue.com");
  int httpCode = http.GET();
  if (httpCode < 0) {
    Serial.print("error getting host address - http code ");
    Serial.println(httpCode);
    Serial.print("Using default host ");
    http.end();
    Serial.println(_defaultHost);
    return String(_defaultHost);
  }
  StaticJsonDocument<192> ipDoc;
  DeserializationError error = deserializeJson(ipDoc, http.getString());
  http.end();
  if (error) {
    Serial.print(F("Unable to read server response: "));
    Serial.println(error.f_str());
    Serial.print("Using default host ");
    Serial.println(_defaultHost);
    return String(_defaultHost);
  }
  return ipDoc[0]["internalipaddress"];
}

void HueController::testLights() {
  
}

vector<HueLight> HueController::getGroupLights(const char* groupName) {
  DynamicJsonDocument groupsDoc = _makeRequest(GET, "groups", "");
  JsonObject groups = groupsDoc.as<JsonObject>();
  vector<HueLight> lights;
  for (JsonPair group : groups) {
    JsonVariant groupInfo = group.value();
    if (strcmp(groupName, groupInfo["name"]) == 0) {
      for (JsonVariant lightId : groupInfo["lights"].as<JsonArray>()) {
        lights.push_back(HueLight(lightId.as<String>()));
      }
      return lights;
    }
  }
  return lights;
}

String HueController::getLightState(HueLight light) {
  String path = String("lights/" + String(light.getId()));
  DynamicJsonDocument doc = _makeGetRequest(path);
  String output;
  serializeJson(doc, output);
  return output;
}

DynamicJsonDocument HueController::_makeGetRequest(String path) {
  return _makeRequest(GET, path, "");
}

DynamicJsonDocument HueController::_makePostRequest(String path, String body) {
  return _makeRequest(POST, path, body);
}

DynamicJsonDocument HueController::_makeRequest(RequestType type, String path, String body) {
  String url = _baseUrl + path;
  Serial.println("request url: " + url);
  HTTPClient http;
  WiFiClient wifi;
  http.useHTTP10(true);
  http.begin(wifi, url);
  http.addHeader("Content-Type", "text/plain");
  int httpCode;
  switch(type) {
    case GET:
      httpCode = http.GET();
      break;
    case POST:
    default:
      httpCode = http.POST(body);
      break;
  }
  if (httpCode < 0) {
    Serial.println("HTTP fetch failed");
    Serial.println("\tURL: " + url);
    Serial.println("\t" + String(httpCode));
  }
  DynamicJsonDocument doc(12288);
  DeserializationError error = deserializeJson(doc, http.getStream());
  if (error) {
    Serial.print(F("deserializeJson failed: "));
    Serial.println(error.f_str());
  }
  http.end();
  return doc;
}
