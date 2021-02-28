#ifndef LV_CLOCK_H
#define LV_CLOCK_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RESOLUTION_320_240  1
#ifdef RESOLUTION_320_240
/* Clock & Date */
#define TIME_DATE_W                     320 
#define TIME_DATE_H                     80 
#define TIME_DATE_ALIGN_CENTER_X        0
#define TIME_DATE_ALIGN_CENTER_Y        80

#define CLOCK_WIDTH                     180 
#define CLOCK_HEIGHT                    60    
#define CLOCK_POS_X                     10
#define CLOCK_POS_Y                     10

#define DATE_WIDTH                      110 
#define DATE_HEIGHT                     60    
#define DATE_POS_X                      200
#define DATE_POS_Y                      10

#define CLOCK_LABEL_ALIGN_CENTER_X      0 
#define CLOCK_LABEL_ALIGN_CENTER_Y      0 
#define DATE_LABEL_IN_TOP_MID_X         0 
#define DATE_LABEL_IN_TOP_MID_Y         10 
#define WEEK_LABEL_IN_BOTTOM_MID_X      0 
#define WEEK_LABEL_IN_BOTTOM_MID_Y      -5 

/* Table View */
#define TABVIEW_TAB_W                           300
#define TABVIEW_TAB_H                           140
#define TABVIEW_TAB_IN_TOP_LEFT_X               10
#define TABVIEW_TAB_IN_TOP_LEFT_Y               10   

/* Weather Now */
#define IMG_NOW_W                               140
#define IMG_NOW_H                               120

#define IMG_NOW_ALIGN_X                         0
#define IMG_NOW_ALIGN_Y                         5

/* Weather Image */
#define IMG_NOW_IN_TOP_MID_X                    0
#define IMG_NOW_IN_TOP_MID_Y                    20
/* Weather Name */
#define IMG_NOW_IN_BOTTOM_MID_X                 0
#define IMG_NOW_IN_BOTTOM_MID_Y                 -5

#define IMG_NOW_TEMP_W                          140
#define IMG_NOW_TEMP_H                          120
#define IMG_NOW_TEMP_ALIGN_X                    140
#define IMG_NOW_TEMP_ALIGN_Y                    5

/* Temp Image */
#define IMG_NOW_TEMP_ALIGN_IN_TOP_LEFT_X        20
#define IMG_NOW_TEMP_ALIGN_IN_TOP_LEFT_Y        15
/* Humi Image */
#define IMG_NOW_TEMP_ALIGN_IN_TOP_RIGHT_X       -10
#define IMG_NOW_TEMP_ALIGN_IN_TOP_RIGHT_Y       15
/* Temp */
#define IMG_NOW_TEMP_ALIGN_IN_BOTTOM_LEFT_X     20
#define IMG_NOW_TEMP_ALIGN_IN_BOTTOM_LEFT_Y     -15
/* Humi */
#define IMG_NOW_TEMP_ALIGN_IN_BOTTOM_RIGHT_X    -10
#define IMG_NOW_TEMP_ALIGN_IN_BOTTOM_RIGHT_Y    -15
/* Location */
#define IMG_NOW_IN_LOCATION_BOTTOM_RIGHT_X      -10            
#define IMG_NOW_IN_LOCATION_BOTTOM_RIGHT_Y       0

/* Weather Forecast */
#define IMG_FORECAST_W                      270
#define IMG_FORECAST_H                      110

#define IMG_FORECAST_DATE_IN_TOP_LEFT_X     25
#define IMG_FORECAST_DATE_IN_TOP_LEFT_Y     0
#define IMG_FORECAST_IN_TOP_LEFT_X          20
#define IMG_FORECAST_IN_TOP_LEFT_Y          20

#define IMG_FORECAST_IN_LEFT_MID_X          25
#define IMG_FORECAST_IN_LEFT_MID_Y          25
#define IMG_FORECAST_IN_BOTTOM_LEFT_X       10
#define IMG_FORECAST_IN_BOTTOM_LEFT_Y       5

#define IMG_FORECAST_DATE_IN_TOP_MID_X      0
#define IMG_FORECAST_DATE_IN_TOP_MID_Y      0
#define IMG_FORECAST_IN_TOP_MID_X           0
#define IMG_FORECAST_IN_TOP_MID_Y           20
#define IMG_FORECAST_CENTER_X               0
#define IMG_FORECAST_CENTER_Y               25
#define IMG_FORECAST_IN_BOTTOM_MID_X        5
#define IMG_FORECAST_IN_BOTTOM_MID_Y        5

#define IMG_FORECAST_DATE_IN_TOP_RIGHT_X    -25
#define IMG_FORECAST_DATE_IN_TOP_RIGHT_Y    0
#define IMG_FORECAST_IN_TOP_RIGHT_X         -20
#define IMG_FORECAST_IN_TOP_RIGHT_Y         20
#define IMG_FORECAST_IN_RIGHT_MID_X         -20
#define IMG_FORECAST_IN_RIGHT_MID_Y         25
#define IMG_FORECAST_IN_BOTTOM_RIGHT_X      -5
#define IMG_FORECAST_IN_BOTTOM_RIGHT_Y      5

#else

/* Clock & Date */
#define TIME_DATE_W     320 
#define TIME_DATE_H     80 
#define TIME_DATE_ALIGN_CENTER_X    0
#define TIME_DATE_ALIGN_CENTER_Y    80

#define CLOCK_WIDTH     180 
#define CLOCK_HEIGHT    60    
#define CLOCK_POS_X     10
#define CLOCK_POS_Y     10

#define DATE_WIDTH      110 
#define DATE_HEIGHT     60    
#define DATE_POS_X      200
#define DATE_POS_Y      10

#define CLOCK_LABEL_ALIGN_CENTER_X    0 
#define CLOCK_LABEL_ALIGN_CENTER_Y    0 
#define DATE_LABEL_IN_TOP_MID_X       0 
#define DATE_LABEL_IN_TOP_MID_Y       10 
#define WEEK_LABEL_IN_BOTTOM_MID_X    0 
#define WEEK_LABEL_IN_BOTTOM_MID_Y    -5 

/* Table View */
#define TABVIEW_TAB_W               300
#define TABVIEW_TAB_H               140
#define TABVIEW_TAB_IN_TOP_LEFT_X   10
#define TABVIEW_TAB_IN_TOP_LEFT_Y   10   

/* Weather Now */
#define IMG_NOW_W                   140
#define IMG_NOW_H                   120

#define IMG_NOW_ALIGN_X             0
#define IMG_NOW_ALIGN_Y             5

#define IMG_NOW_W_ALIGN_X           0
#define IMG_NOW_W_ALIGN_Y           20
#define IMG_NOW_W_NAME_ALIGN_X      0
#define IMG_NOW_W_NAME_ALIGN_Y      -20

#define IMG_NOW_TEMP_W                          140
#define IMG_NOW_TEMP_H                          120
#define IMG_NOW_TEMP_ALIGN_X                    140
#define IMG_NOW_TEMP_ALIGN_Y                    5

#define IMG_NOW_TEMP_ALIGN_IN_TOP_LEFT_X        20
#define IMG_NOW_TEMP_ALIGN_IN_TOP_LEFT_Y        15
#define IMG_NOW_TEMP_ALIGN_IN_BOTTOM_LEFT_X     20
#define IMG_NOW_TEMP_ALIGN_IN_BOTTOM_LEFT_Y     -10

#define IMG_NOW_TEMP_ALIGN_IN_TOP_RIGHT_X       -20
#define IMG_NOW_TEMP_ALIGN_IN_TOP_RIGHT_Y       15
#define IMG_NOW_TEMP_ALIGN_IN_BOTTOM_RIGHT_X    -20
#define IMG_NOW_TEMP_ALIGN_IN_BOTTOM_RIGHT_Y    -10

/* Weather Forecast */
#define IMG_FORECAST_W          270
#define IMG_FORECAST_H          110

#define IMG_FORECAST_DATE_IN_TOP_LEFT_X     25
#define IMG_FORECAST_DATE_IN_TOP_LEFT_Y     0
#define IMG_FORECAST_IN_TOP_LEFT_X          20
#define IMG_FORECAST_IN_TOP_LEFT_Y          20

#define IMG_FORECAST_IN_LEFT_MID_X          20
#define IMG_FORECAST_IN_LEFT_MID_Y          25
#define IMG_FORECAST_IN_BOTTOM_LEFT_X       10
#define IMG_FORECAST_IN_BOTTOM_LEFT_Y       5

#define IMG_FORECAST_DATE_IN_TOP_MID_X      0
#define IMG_FORECAST_DATE_IN_TOP_MID_Y      0
#define IMG_FORECAST_IN_TOP_MID_X           0
#define IMG_FORECAST_IN_TOP_MID_Y           20
#define IMG_FORECAST_CENTER_X               0
#define IMG_FORECAST_CENTER_Y               25
#define IMG_FORECAST_IN_BOTTOM_MID_X        5
#define IMG_FORECAST_IN_BOTTOM_MID_Y        5

#define IMG_FORECAST_DATE_IN_TOP_RIGHT_X    -25
#define IMG_FORECAST_DATE_IN_TOP_RIGHT_Y    0
#define IMG_FORECAST_IN_TOP_RIGHT_X         -20
#define IMG_FORECAST_IN_TOP_RIGHT_Y         20
#define IMG_FORECAST_IN_RIGHT_MID_X         -20
#define IMG_FORECAST_IN_RIGHT_MID_Y         25
#define IMG_FORECAST_IN_BOTTOM_RIGHT_X      -10
#define IMG_FORECAST_IN_BOTTOM_RIGHT_Y      5
#endif


typedef struct _LV_CLOCK_S
{
    lv_obj_t *location;
    lv_obj_t *weather;
    lv_obj_t *weather_name;
    lv_obj_t * temp_img;
    lv_obj_t * temp;
    lv_obj_t * humi_img;
    lv_obj_t * humi;

    lv_obj_t *clock_label;
    lv_obj_t *date_label;
    lv_obj_t *week_label;
}LV_CLOCK_S;

typedef struct _LV_CLOCK_TIME_S
{
    int year;
    int mon;
    int mday;
    int wday;
    int hour;
    int min;
    int sec;
}LV_CLOCK_TIME_S;

typedef struct _LV_CLOCK_WEATHER_S
{
    char location[16];
    int code;
    int temp;
    int humi;
}LV_CLOCK_WEATHER_S;

typedef struct _CLOCK_FORECAST_S
{
    char datestr[12];
    int tmp_min;
    int tmp_max;
    int icon_code;
}LV_CLOCK_FORECAST_S;

void lv_clock(void);

void lv_clock_now(LV_CLOCK_TIME_S time, LV_CLOCK_WEATHER_S weather);

void lv_clock_forecast(LV_CLOCK_FORECAST_S *forecast);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  
