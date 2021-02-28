#include <Arduino.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>

#include <time.h>                       
#include <sys/time.h>
#include <stdio.h>

#include "base.h"
#include "HeFeng.h"
#include "Seniverse.h"

#include "display.h"
#include "touch.h"
#include "sdcard.h"
#include "lv_gui.h"
#include "lv_clock.h"


#define TZ              8      // 中国时区为8
#define DST_MN          0      // 默认为0

#define TZ_MN           ((TZ)*60)   //时间换算
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)

/* 和风天气 - https://dev.heweather.com */
const char *HEFENG_KEY = "";//和风天气秘钥,替换成自己的秘钥
const char *HEFENG_LOCATION = "101280306";//城市ID,可到https://where.heweather.com/index.html查询,替换成自己的城市ID

/* 心知天气 - https://www.seniverse.com */
const char *SENIVERSE_KEY = "";//心知天气秘钥,替换成自己的秘钥
const char *SENIVERSE_LOCATION = "Huicheng";//城市列表 https://docs.seniverse.com/api/start/start.html,替换成自己的城市名称

const int UPDATE_INTERVAL_SECS = 10 * 60; //10分钟更新一次天气
const int UPDATE_CURR_INTERVAL_SECS = 30 * 60; // 30分钟更新一次粉丝数
const char *BILIBILIID = "36549646";  //B站账号

/*** Component objects ***/
Display screen;
#if USE_TOUCH
Touch touch;
#endif
HeFengCurrentData currentWeather;
HeFengForeData foreWeather[3];
HeFeng HeFengClient;
Seniverse SeniverseClient;

#if USE_SDCARD
SdCard tf;
#endif

static time_t unixTime;
static struct tm *timeinfo;
static LV_CLOCK_TIME_S stTime;
static LV_CLOCK_WEATHER_S stWeather;
static LV_CLOCK_FORECAST_S stForecast[3];

long date = 0;
bool readyForWeatherUpdate = false; // 天气更新标志
bool first = true;  //首次更新标志
long timeSinceLastWUpdate = 0;    //上次更新后的时间
long timeSinceLastCurrUpdate = 0;   //上次天气更新后的时间
String fans = "-1"; //粉丝数


void webconnect() {  ////Web配网
    WiFiManager wifiManager;  //实例化WiFiManager
    wifiManager.setDebugOutput(false); //关闭Debug

    //AP模式
    if (!wifiManager.autoConnect("Clock"))
    {
        Serial.println("连接失败并超时");
        ESP.restart();
        delay(1000);
    }

    yield();
    Serial.println("Connected...^_^");
}

void update() {
    HeFengClient.doUpdateCurr(&currentWeather, HEFENG_KEY, HEFENG_LOCATION);
    HeFengClient.doUpdateFore(foreWeather, HEFENG_KEY, HEFENG_LOCATION);

    if ((39 == currentWeather.icon_code) || (39 == foreWeather[0].icon_code)) {
        SeniverseClient.doUpdateCurr((SeniverseCurrentData *)&currentWeather, SENIVERSE_KEY, SENIVERSE_LOCATION);
        SeniverseClient.doUpdateFore((SeniverseForeData *)foreWeather, SENIVERSE_KEY, SENIVERSE_LOCATION);
    }
}

void setup(void) {
    Serial.begin(115200);
    Serial.println("Setup...");

    /*** Init screen ***/
    screen.init();

#if USE_TOUCH
    touch.init();
#endif

    /*** Init micro SD-Card ***/
#if USE_SDCARD
	tf.init();
#endif

    /*** Web配网 ***/
    webconnect();

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    /*** ntp获取时间，你也可用其他"pool.ntp.org","0.cn.pool.ntp.org","1.cn.pool.ntp.org","ntp1.aliyun.com" ***/
    Serial.println("SyncTime...");
    configTime(TZ_SEC, DST_SEC, "ntp.ntsc.ac.cn", "ntp1.aliyun.com");

    sprintf(stWeather.location, "%s", "Huizhou");

    /*** Inflate GUI objects ***/    
    lv_gui();

    date = millis();
}

void loop() {
    // run this as often as possible
    screen.routine();

    if (first) {
        update();
        first = false;
    }

    if (millis() - timeSinceLastWUpdate > (1000L * UPDATE_INTERVAL_SECS)) { //屏幕刷新
        timeSinceLastWUpdate = millis();
        update();
    }

    if (millis() - timeSinceLastCurrUpdate > (1000L * UPDATE_CURR_INTERVAL_SECS)) { //粉丝数更新
        HeFengClient.fans(&currentWeather, BILIBILIID);
        fans = String(currentWeather.follower);
        timeSinceLastCurrUpdate = millis();
    }

    delay(5);
    if (millis() - date > 500)
    {
        date = millis();
        unixTime = time(NULL);
        timeinfo = localtime(&unixTime);

        /* Time */
        stTime.year = timeinfo->tm_year+1900;
        stTime.mon = timeinfo->tm_mon + 1;
        stTime.mday = timeinfo->tm_mday;
        stTime.wday = timeinfo->tm_wday;
        stTime.hour = timeinfo->tm_hour;
        stTime.min = timeinfo->tm_min;
        stTime.sec = timeinfo->tm_sec;

        stWeather.code = currentWeather.icon_code;
        stWeather.temp = atoi(currentWeather.tmp.c_str());
        stWeather.humi = atoi(currentWeather.hum.c_str());
        if (0 == stWeather.humi) {
            stWeather.humi = 50;
        }

        lv_clock_now(stTime, stWeather);

        /* Weather Forecast */
        sprintf(stForecast[0].datestr, "%s", foreWeather[0].datestr.c_str());
        stForecast[0].tmp_min = atoi(foreWeather[0].tmp_min.c_str());
        stForecast[0].tmp_max = atoi(foreWeather[0].tmp_max.c_str());
        stForecast[0].icon_code = foreWeather[0].icon_code;

        sprintf(stForecast[1].datestr, "%s", foreWeather[1].datestr.c_str());
        stForecast[1].tmp_min = atoi(foreWeather[1].tmp_min.c_str());
        stForecast[1].tmp_max = atoi(foreWeather[1].tmp_max.c_str());
        stForecast[1].icon_code = foreWeather[1].icon_code;

        sprintf(stForecast[2].datestr, "%s", foreWeather[2].datestr.c_str());
        stForecast[2].tmp_min = atoi(foreWeather[2].tmp_min.c_str());
        stForecast[2].tmp_max = atoi(foreWeather[2].tmp_max.c_str());
        stForecast[2].icon_code = foreWeather[2].icon_code;
        lv_clock_forecast((LV_CLOCK_FORECAST_S *)stForecast);
    }
}

