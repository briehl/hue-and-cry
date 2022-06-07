#ifndef HUE_LIGHT_H
#define HUE_LIGHT_H

#include "Arduino.h"

class HueLight
{
  public:
    HueLight(String id);
    void setState();
    void setHue(unsigned int hue);
    unsigned int getHue();
    void setBrightness(unsigned int brightness);
    unsigned int getBrightness();
    void setSaturation(unsigned int saturation);
    unsigned int getSaturation();
    void setOn(bool isOn);
    bool getOn();
    String getId();
    String getState();
  private:
    String _id;
    bool _on;
    unsigned int _hue;
    unsigned int _bri;
    unsigned int _sat;
    float _xy[2];
    
    
    
};

#endif

//WM3902279
//KSM150PSTG
