#include "hue_light.h"

HueLight::HueLight(String id) {
  _id = id;
}

String HueLight::getId() {
  return _id;
}

void HueLight::setColor(const char* color) {
  _hue = color;
}

const char* HueLight::getColor() {
  return _hue;
}

void HueLight::setBrightness(const char* brightness) {
  _bri = brightness;
}

const char* HueLight::getBrightness() {
  return _bri;
}
