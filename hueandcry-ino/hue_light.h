#ifndef HUE_LIGHT_H
#define HUE_LIGHT_H

#include "Arduino.h"

class HueLight
{
  public:
    HueLight(String id);
    void setState();
    void setColor(const char* color);
    const char* getColor();
    void setBrightness(const char* brightness);
    const char* getBrightness();
    String getId();
  private:
    String _id;
    const char* _hue;
    const char* _bri;
};

#endif

//WM3902279
//KSM150PSTG
