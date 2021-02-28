
#pragma once
#include <ArduinoJson.h>

typedef struct SeniverseCurrentData {
    String cond_txt;
    String fl;
    String tmp;
    String hum;
    String wind_sc;
    String follower;
    int icon_code;
}SeniverseCurrentData;

typedef struct SeniverseForeData {
    String datestr;
    String tmp_min;
    String tmp_max;
    int icon_code;
}SeniverseForeData;

class Seniverse {
  private:
    int getIconCode(String cond_code);
  public:
    Seniverse();
    void doUpdateCurr(SeniverseCurrentData *data, String key, String location);
    void doUpdateFore(SeniverseForeData *data, String key, String location);
    void fans(SeniverseCurrentData *data, String id);
};
