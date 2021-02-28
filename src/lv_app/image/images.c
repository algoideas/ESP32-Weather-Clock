#include "images.h"

LV_IMG_DECLARE(sunny);
LV_IMG_DECLARE(clear);
LV_IMG_DECLARE(cloudy);
LV_IMG_DECLARE(partly_cloudy);
LV_IMG_DECLARE(mostly_cloudy);
LV_IMG_DECLARE(overcast);
LV_IMG_DECLARE(shower);
LV_IMG_DECLARE(thunder_shower);
LV_IMG_DECLARE(light_rain);
LV_IMG_DECLARE(moderate_rain);
LV_IMG_DECLARE(heavy_rain);
LV_IMG_DECLARE(storm);
LV_IMG_DECLARE(ice_rain);
LV_IMG_DECLARE(sleet);
LV_IMG_DECLARE(snow_flurry);
LV_IMG_DECLARE(light_snow);
LV_IMG_DECLARE(moderate_snow);
LV_IMG_DECLARE(heavy_snow);
LV_IMG_DECLARE(sand);
LV_IMG_DECLARE(sand_storm);
LV_IMG_DECLARE(foggy);
LV_IMG_DECLARE(haze);
LV_IMG_DECLARE(windy);
LV_IMG_DECLARE(tropical_storm);
LV_IMG_DECLARE(cold);
LV_IMG_DECLARE(unknown);

//https://docs.seniverse.com/api/start/code.html
const struct LV_WEATHER lv_weather[40] = 
{
    {"Sunny", &sunny},/* 晴（国内城市白天晴） - 0 */
    {"Clear", &clear}, /* 晴（国内城市夜晚晴） - 1 */
    {"Fair", &sunny},  /* 晴（国外城市白天晴） - 2 */
    {"Fair", &clear}, /* 晴（国外城市夜晚晴） - 3 */
    {"Cloudy", &cloudy},/* 多云 - 4 */
    {"Partly Cloudy", &partly_cloudy}, /* 晴间多云 - 5 */
    {"Partly Cloudy", &mostly_cloudy}, /* 晴间多云 - 6 */
    {"Mostly Cloudy", &partly_cloudy}, /* 大部多云 - 7 */
    {"Mostly Cloudy", &mostly_cloudy}, /* 大部多云 - 8 */
    {"Overcast", &overcast}, /* 阴 - 9 */
    {"Shower", &shower}, /* 阵雨 - 10 */
    {"Thundershower", &thunder_shower},/* 雷阵雨 - 11 */
    {"Thundershower with Hail", &thunder_shower}, /* 雷阵雨伴有冰雹 - 12 */
    {"Light Rain", &light_rain}, /* 小雨 - 13 */
    {"Moderate Rain", &moderate_rain}, /* 中雨 - 14 */
    {"Heavy Rain", &storm}, /* 大雨 - 15 */
    {"Storm", &storm}, /* 暴雨 - 16 */
    {"Heavy Storm", &storm}, /* 大暴雨 - 17 */
    {"Severe Storm", &storm}, /* 特大暴雨 - 18 */
    {"Ice Rain", &ice_rain}, /* 冻雨 - 19 */
    {"Sleet", &sleet}, /* 雨夹雪 - 20 */
    {"Snow Flurry", &snow_flurry}, /* 阵雪 - 21 */
    {"Light Snow", &light_snow}, /* 小雪 - 22 */
    {"Moderate Snow", &moderate_snow}, /* 中雪 - 23 */
    {"Heavy Snow", &heavy_snow}, /* 大雪 - 24 */
    {"Snowstorm", &heavy_snow}, /* 暴雪 - 25 */
    {"Dust", &sand}, /* 浮尘 - 26 */
    {"Sand", &sand}, /* 扬沙 - 27 */
    {"Duststorm", &sand_storm}, /* 沙尘暴 - 28 */
    {"Sandstorm", &sand_storm}, /* 强沙尘暴 - 29 */
    {"Foggy", &foggy}, /* 雾 - 30 */
    {"Haze", &haze}, /* 霾 - 31 */
    {"Windy", &windy}, /* 风 - 32 */
    {"Blustery", &windy}, /* 大风 - 33 */
    {"Hurricane", &windy}, /* 飓风 - 34 */
    {"Tropical Storm", &tropical_storm}, /* 热带风暴 - 35 */
    {"Tornado", &tropical_storm}, /* 龙卷风 - 36 */
    {"Cold", &cold}, /* 冷 - 37 */
    {"Hot", &sunny}, /* 热 - 38 */
    {"Unknown", &unknown}, /* 未知 - 99 */
};