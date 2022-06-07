#include "hue_light.h"
#include <ArduinoJson.h>

HueLight::HueLight(String id) {
  _id = id;
}

String HueLight::getId() {
  return _id;
}

void HueLight::setHue(unsigned int hue) {
  _hue = hue;
}

unsigned int HueLight::getHue() {
  return _hue;
}

void HueLight::setBrightness(unsigned int brightness) {
  _bri = brightness;
}

unsigned int HueLight::getBrightness() {
  return _bri;
}

void HueLight::setSaturation(unsigned int saturation) {
  _sat = saturation;
}

unsigned int HueLight::getSaturation() {
  return _sat;
}

void HueLight::setOn(bool isOn) {
  _on = isOn;
}

bool HueLight::getOn() {
  return _on;
}

String HueLight::getState() {
  StaticJsonDocument<96> stateDoc;
  stateDoc["hue"] = _hue;
  stateDoc["sat"] = _sat;
  stateDoc["bri"] = _bri;
  stateDoc["on"] = _on;
  String state;
  serializeJson(stateDoc, state);
  return state;  
}
