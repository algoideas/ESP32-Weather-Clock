
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "Seniverse.h"


Seniverse::Seniverse() {
}

void Seniverse::fans(SeniverseCurrentData *data, String id) { 
  std::unique_ptr<WiFiClientSecure>client(new WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;
  String url = "https://api.bilibili.com/x/relation/stat?vmid=" + id;
  Serial.print("[HTTPS] begin...bilibili\r\n");
  if (https.begin(*client, url)) {  // HTTPS
    // start connection and send HTTP header
    int httpCode = https.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\r\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
        DynamicJsonDocument  jsonBuffer(2048);
        deserializeJson(jsonBuffer, payload);
        JsonObject root = jsonBuffer.as<JsonObject>();

        String follower = root["data"]["follower"];
        data->follower = follower;
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\r\n", https.errorToString(httpCode).c_str());
      data->follower = "-1";
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\r\n");
    data->follower = "-1";
  }
}

void Seniverse::doUpdateCurr(SeniverseCurrentData *data, String key, String location) { 

  std::unique_ptr<WiFiClientSecure>client(new WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;
  String url = "https://api.seniverse.com/v3/weather/now.json?key=" + key + "&location=" + location + "&language=zh-Hans&unit=c";
  Serial.print("[HTTPS] begin...now\r\n");
  if (https.begin(*client, url)) {  // HTTPS
    // start connection and send HTTP header
    int httpCode = https.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\r\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
        DynamicJsonDocument  jsonBuffer(2048);
        deserializeJson(jsonBuffer, payload);
        JsonObject root = jsonBuffer.as<JsonObject>();

        String tmp = root["results"][0]["now"]["temperature"];
        data->tmp = tmp;
        String fl = root["results"][0]["now"]["wind_scale"]; //风力等级，请参考：http://baike.baidu.com/view/465076.htm
        data->fl = fl;
        String hum = root["results"][0]["now"]["humidity"];
        data->hum = hum;
        String wind_sc = root["results"][0]["now"]["wind_direction"];
        data->wind_sc = wind_sc;
        String cond_code = root["results"][0]["now"]["code"];
        String cond_txt = root["results"][0]["now"]["text"];
        data->cond_txt = cond_txt;
        data->icon_code = getIconCode(cond_code);

      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\r\n", https.errorToString(httpCode).c_str());
      data->tmp = "-1";
      data->fl = "-1";
      data->hum = "-1";
      data->wind_sc = "-1";
      data->cond_txt = "no network";
      data->icon_code = 39;
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\r\n");
    data->tmp = "-1";
    data->fl = "-1";
    data->hum = "-1";
    data->wind_sc = "-1";
    data->cond_txt = "no network";
    data->icon_code = 39;
  }

}

void Seniverse::doUpdateFore(SeniverseForeData *data, String key, String location) { 

  std::unique_ptr<WiFiClientSecure>client(new WiFiClientSecure);
  client -> setInsecure();
  HTTPClient https;
  String url = "https://api.seniverse.com/v3/weather/daily.json?key=" + key + "&location=" + location + "&language=zh-Hans&unit=c&start=0&days=3";
  Serial.print("[HTTPS] begin...forecast\r\n");
  if (https.begin(*client, url)) {  // HTTPS
    // start connection and send HTTP header
    int httpCode = https.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\r\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
        DynamicJsonDocument  jsonBuffer(8192);
        deserializeJson(jsonBuffer, payload);
        JsonObject root = jsonBuffer.as<JsonObject>();
        int i;
        for (i = 0; i < 3; i++) {
          String tmp_min = root["results"][0]["daily"][i]["low"];
          data[i].tmp_min = tmp_min;
          String tmp_max = root["results"][0]["daily"][i]["high"];
          data[i].tmp_max = tmp_max;
          String datestr = root["results"][0]["daily"][i]["date"];
          data[i].datestr = datestr.substring(5, datestr.length());
          String cond_code = root["results"][0]["daily"][i]["code_day"];
          data[i].icon_code = getIconCode(cond_code);
        }
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\r\n", https.errorToString(httpCode).c_str());
      int i;
      for (i = 0; i < 3; i++) {
        data[i].tmp_min = "-1";
        data[i].tmp_max = "-1";
        data[i].datestr = "-1";
        data[i].icon_code = 39;
      }
    }
    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\r\n");
    int i;
    for (i = 0; i < 3; i++) {
      data[i].tmp_min = "-1";
      data[i].tmp_max = "-1";
      data[i].datestr = "-1";
      data[i].icon_code = 39;
    }
  }
}

/* 天气现象代码: https://docs.seniverse.com/api/start/code.html */
int Seniverse::getIconCode(String cond_code) {
    int code = 0;

    code = atoi(cond_code.c_str());
    if ((code < 0) || (code > 39)) {
        return 39;
    }

    return code;
}


