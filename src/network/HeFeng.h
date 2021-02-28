
#pragma once
#include <ArduinoJson.h>

typedef struct HeFengCurrentData {
    String cond_txt;
    String fl;
    String tmp;
    String hum;
    String wind_sc;
    String follower;
    int icon_code;
}HeFengCurrentData;

typedef struct HeFengForeData {
    String datestr;
    String tmp_min;
    String tmp_max;
    int icon_code;
}HeFengForeData;

class HeFeng {
  private:
    int getIconCode(String cond_code);
  public:
    HeFeng();
    void doUpdateCurr(HeFengCurrentData *data, String key, String location);
    void doUpdateFore(HeFengForeData *data, String key, String location);
    void fans(HeFengCurrentData *data, String id);
};
