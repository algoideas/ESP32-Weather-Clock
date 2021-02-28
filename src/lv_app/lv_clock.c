/*********************
 *      INCLUDES
 *********************/
#include "lv_clock.h"
#include "fonts.h"
#include "images.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _LV_FORECAST_INFO_S
{
	lv_obj_t *date;
	lv_obj_t *weather;
	lv_obj_t *weather_name;
	lv_obj_t *temp;
}LV_FORECAST_INFO_S;

static lv_obj_t *pstWall;
static lv_task_t *pstTask;
static lv_obj_t *pstTabview;

static LV_CLOCK_S stClock;
static LV_CLOCK_TIME_S stTime;
static LV_CLOCK_WEATHER_S stWeather;
static LV_CLOCK_FORECAST_S stForecast[3];

static LV_FORECAST_INFO_S stForecastInfo[3];


static void clock_task(lv_task_t *t)
{
	static unsigned char count = 0;
    static unsigned int curr_id = 0;
    static const char *week[7] = { "日","一","二","三","四","五","六" };

    lv_label_set_text_fmt(stClock.clock_label, "%.2d:%.2d:%.2d", stTime.hour, stTime.min, stTime.sec);
    lv_label_set_text_fmt(stClock.date_label, "%d.%.2d.%.2d", stTime.year, 
            stTime.mon, stTime.mday);
    lv_label_set_text_fmt(stClock.week_label, "星期%s", week[stTime.wday]);

	lv_obj_align(stClock.clock_label, lv_obj_get_parent(stClock.clock_label),
		LV_ALIGN_CENTER, CLOCK_LABEL_ALIGN_CENTER_X, CLOCK_LABEL_ALIGN_CENTER_Y);
	lv_obj_align(stClock.date_label, lv_obj_get_parent(stClock.date_label),
		LV_ALIGN_IN_TOP_MID, DATE_LABEL_IN_TOP_MID_X, DATE_LABEL_IN_TOP_MID_Y);
	lv_obj_align(stClock.week_label, lv_obj_get_parent(stClock.week_label),
		LV_ALIGN_IN_BOTTOM_MID, WEEK_LABEL_IN_BOTTOM_MID_X, WEEK_LABEL_IN_BOTTOM_MID_Y);

	if (0 == (++count % 50))
	{
		lv_tabview_set_tab_act(pstTabview, !curr_id, LV_ANIM_ON);
		count = 0;
		curr_id = lv_tabview_get_tab_act(pstTabview);
	}

    /* Forecast */
    if (curr_id)
    {
    	lv_label_set_text_fmt(stForecastInfo[0].date, "%s", stForecast[0].datestr);
    	lv_label_set_text_fmt(stForecastInfo[1].date, "%s", stForecast[1].datestr);
    	lv_label_set_text_fmt(stForecastInfo[2].date, "%s", stForecast[2].datestr);

        lv_label_set_text_fmt(stForecastInfo[0].weather_name, "%s", lv_weather[stForecast[0].icon_code].weathername);
        lv_img_set_src(stForecastInfo[0].weather, (const lv_img_dsc_t*)lv_weather[stForecast[0].icon_code].img_dsc);
        lv_label_set_text_fmt(stForecastInfo[1].weather_name, "%s", lv_weather[stForecast[1].icon_code].weathername);
        lv_img_set_src(stForecastInfo[1].weather, (const lv_img_dsc_t*)lv_weather[stForecast[1].icon_code].img_dsc);
        lv_label_set_text_fmt(stForecastInfo[2].weather_name, "%s", lv_weather[stForecast[2].icon_code].weathername);
        lv_img_set_src(stForecastInfo[2].weather, (const lv_img_dsc_t*)lv_weather[stForecast[2].icon_code].img_dsc);

    	lv_label_set_text_fmt(stForecastInfo[0].temp, "%d-%d℃", stForecast[0].tmp_min, stForecast[0].tmp_max);
    	lv_label_set_text_fmt(stForecastInfo[1].temp, "%d-%d℃", stForecast[1].tmp_min, stForecast[1].tmp_max);
    	lv_label_set_text_fmt(stForecastInfo[2].temp, "%d-%d℃", stForecast[2].tmp_min, stForecast[2].tmp_max);
    
		lv_obj_align(stForecastInfo[0].date, lv_obj_get_parent(stForecastInfo[0].date),
				LV_ALIGN_IN_TOP_LEFT, IMG_FORECAST_DATE_IN_TOP_LEFT_X, IMG_FORECAST_DATE_IN_TOP_LEFT_Y);
		lv_obj_align(stForecastInfo[0].weather, lv_obj_get_parent(stForecastInfo[0].weather),
				LV_ALIGN_IN_TOP_LEFT, IMG_FORECAST_IN_TOP_LEFT_X, IMG_FORECAST_IN_TOP_LEFT_Y);
		lv_obj_align(stForecastInfo[0].weather_name, lv_obj_get_parent(stForecastInfo[0].weather_name),
				LV_ALIGN_IN_LEFT_MID, IMG_FORECAST_IN_LEFT_MID_X, IMG_FORECAST_IN_LEFT_MID_Y);
		lv_obj_align(stForecastInfo[0].temp, lv_obj_get_parent(stForecastInfo[0].temp),
				LV_ALIGN_IN_BOTTOM_LEFT, IMG_FORECAST_IN_BOTTOM_LEFT_X, IMG_FORECAST_IN_BOTTOM_LEFT_Y);

		lv_obj_align(stForecastInfo[1].date, lv_obj_get_parent(stForecastInfo[1].date),
				LV_ALIGN_IN_TOP_MID, IMG_FORECAST_DATE_IN_TOP_MID_X, IMG_FORECAST_DATE_IN_TOP_MID_Y);
		lv_obj_align(stForecastInfo[1].weather, lv_obj_get_parent(stForecastInfo[1].weather),
				LV_ALIGN_IN_TOP_MID, IMG_FORECAST_IN_TOP_MID_X, IMG_FORECAST_IN_TOP_MID_Y);
		lv_obj_align(stForecastInfo[1].weather_name, lv_obj_get_parent(stForecastInfo[1].weather_name),
				LV_ALIGN_CENTER, IMG_FORECAST_CENTER_X, IMG_FORECAST_CENTER_Y);
		lv_obj_align(stForecastInfo[1].temp, lv_obj_get_parent(stForecastInfo[1].temp),
				LV_ALIGN_IN_BOTTOM_MID, IMG_FORECAST_IN_BOTTOM_MID_X, IMG_FORECAST_IN_BOTTOM_MID_Y);

		lv_obj_align(stForecastInfo[2].date, lv_obj_get_parent(stForecastInfo[2].date),
				LV_ALIGN_IN_TOP_RIGHT, IMG_FORECAST_DATE_IN_TOP_RIGHT_X, IMG_FORECAST_DATE_IN_TOP_RIGHT_Y);
		lv_obj_align(stForecastInfo[2].weather, lv_obj_get_parent(stForecastInfo[2].weather),
				LV_ALIGN_IN_TOP_RIGHT, IMG_FORECAST_IN_TOP_RIGHT_X, IMG_FORECAST_IN_TOP_RIGHT_Y);
		lv_obj_align(stForecastInfo[2].weather_name, lv_obj_get_parent(stForecastInfo[2].weather_name),
				LV_ALIGN_IN_RIGHT_MID, IMG_FORECAST_IN_RIGHT_MID_X, IMG_FORECAST_IN_RIGHT_MID_Y);
		lv_obj_align(stForecastInfo[2].temp, lv_obj_get_parent(stForecastInfo[2].temp),
				LV_ALIGN_IN_BOTTOM_RIGHT, IMG_FORECAST_IN_BOTTOM_RIGHT_X, IMG_FORECAST_IN_BOTTOM_RIGHT_Y);
	}
    else
    {
        lv_label_set_text_fmt(stClock.location, "%s", stWeather.location);
        lv_label_set_text_fmt(stClock.weather_name, "%s", lv_font[stWeather.code].name);
        lv_img_set_src(stClock.weather, (const lv_img_dsc_t*)lv_weather[stWeather.code].img_dsc);
        lv_label_set_text_fmt(stClock.temp, "%d℃", stWeather.temp);
        lv_label_set_text_fmt(stClock.humi, "%d%%", stWeather.humi);

        lv_obj_align(stClock.location, lv_obj_get_parent(stClock.location), 
            LV_ALIGN_IN_BOTTOM_RIGHT, IMG_NOW_IN_LOCATION_BOTTOM_RIGHT_X, IMG_NOW_IN_LOCATION_BOTTOM_RIGHT_Y);
		lv_obj_align(stClock.weather, lv_obj_get_parent(stClock.weather),
			LV_ALIGN_IN_TOP_MID, IMG_NOW_IN_TOP_MID_X, IMG_NOW_IN_TOP_MID_Y);
		lv_obj_align(stClock.weather_name, lv_obj_get_parent(stClock.weather_name),
			LV_ALIGN_IN_BOTTOM_MID, IMG_NOW_IN_BOTTOM_MID_X, IMG_NOW_IN_BOTTOM_MID_Y);

		lv_obj_align(stClock.temp, lv_obj_get_parent(stClock.temp),
			LV_ALIGN_IN_BOTTOM_LEFT, IMG_NOW_TEMP_ALIGN_IN_BOTTOM_LEFT_X, IMG_NOW_TEMP_ALIGN_IN_BOTTOM_LEFT_Y);
		lv_obj_align(stClock.humi, lv_obj_get_parent(stClock.humi),
			LV_ALIGN_IN_BOTTOM_RIGHT, IMG_NOW_TEMP_ALIGN_IN_BOTTOM_RIGHT_X, IMG_NOW_TEMP_ALIGN_IN_BOTTOM_RIGHT_Y);
    }
}

void lv_clock(void)
{
    static lv_style_t time_style;
    static lv_style_t clock_style;
    static lv_style_t date_style;
    static lv_style_t weather_style;
    static lv_style_t weather_name_style;
    static lv_style_t img_style;
    static lv_style_t humi_label_style;
    static lv_style_t clock_label_style;
    static lv_style_t date_label_style;
    static lv_style_t location_label_style;
    static lv_style_t week_lable_style;

    lv_style_init(&time_style);
    lv_style_set_radius(&time_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_opa(&time_style, LV_STATE_DEFAULT, LV_OPA_20);
    lv_style_set_border_width(&time_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&time_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    lv_style_init(&clock_style);
    lv_style_set_bg_opa(&clock_style, LV_STATE_DEFAULT, LV_OPA_20);
    lv_style_set_border_width(&clock_style, LV_STATE_DEFAULT, 0);
    lv_style_set_clip_corner(&clock_style, 0, true);
    lv_style_set_radius(&clock_style, 0, 8);
    lv_style_set_bg_color(&clock_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    lv_style_init(&date_style);
    lv_style_copy(&date_style, &clock_style);

	/* Clock font */
    lv_style_init(&clock_label_style);
    lv_style_set_text_color(&clock_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&clock_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_32);
    lv_style_set_text_opa(&clock_label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_opa(&clock_label_style, LV_STATE_DEFAULT, LV_OPA_0);

	/* Date font */
    lv_style_init(&date_label_style);
    lv_style_copy(&date_label_style, &clock_label_style);
    lv_style_set_text_color(&date_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&date_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_16);

	/* Location font */
    lv_style_init(&location_label_style);
    lv_style_set_text_color(&location_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&location_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_style_set_text_opa(&location_label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_opa(&location_label_style, LV_STATE_DEFAULT, LV_OPA_0);

	/* Weather font */
    lv_style_init(&weather_name_style);
    lv_style_copy(&weather_name_style, &clock_label_style);
    lv_style_set_text_color(&weather_name_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&weather_name_style, LV_STATE_DEFAULT, &weather_font);

	/* Humiture font */
    lv_style_init(&humi_label_style);
    lv_style_copy(&humi_label_style, &clock_label_style);
    lv_style_set_text_color(&humi_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&humi_label_style, LV_STATE_DEFAULT, &humiture_font);

	/* Week font */
    lv_style_init(&week_lable_style);
    lv_style_copy(&week_lable_style, &clock_label_style);
    lv_style_set_text_color(&week_lable_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&week_lable_style, LV_STATE_DEFAULT, &week_font);

    /* Weather style */
    lv_style_init(&weather_style);
    lv_style_set_bg_opa(&weather_style, LV_STATE_DEFAULT, LV_OPA_20);
    lv_style_set_border_width(&weather_style, LV_STATE_DEFAULT, 0);
    lv_style_set_clip_corner(&weather_style, 0, true);
    lv_style_set_radius(&weather_style, 0, 8);
    lv_style_set_bg_color(&weather_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

	/* Img style */
	lv_style_init(&img_style);
	lv_style_set_bg_opa(&img_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);
	lv_style_set_border_width(&img_style, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&img_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

	/* Wall */
	pstWall = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(pstWall, &wallpaper);

    /* Weather Tab view */
    pstTabview = lv_tabview_create(pstWall, NULL);
    lv_obj_set_click(pstTabview, false);
    lv_obj_set_size(pstTabview, TABVIEW_TAB_W, TABVIEW_TAB_H);
    lv_tabview_set_btns_pos(pstTabview, LV_TABVIEW_TAB_POS_NONE);
    lv_obj_align(pstTabview, pstWall, LV_ALIGN_IN_TOP_LEFT, TABVIEW_TAB_IN_TOP_LEFT_X, TABVIEW_TAB_IN_TOP_LEFT_Y);
    lv_obj_add_style(pstTabview, LV_OBJ_PART_MAIN, &weather_style);

    lv_obj_t *weather_now = lv_tabview_add_tab(pstTabview, "Now");
    lv_obj_t *weather_forecast = lv_tabview_add_tab(pstTabview, "Forecast");

	/* Curret Weather Display */
    lv_obj_t *img_now = lv_obj_create(weather_now, NULL);
    lv_obj_set_click(img_now, false);
    lv_obj_set_size(img_now, IMG_NOW_W, IMG_NOW_H);
    lv_obj_align(img_now, weather_now, LV_ALIGN_IN_TOP_LEFT, IMG_NOW_ALIGN_X, IMG_NOW_ALIGN_Y);
    lv_obj_add_style(img_now, LV_OBJ_PART_MAIN, &img_style);

    /* Weather Image */
    stClock.weather = lv_img_create(img_now, NULL);
    lv_img_set_src(stClock.weather, (const lv_img_dsc_t*)lv_weather[0].img_dsc);

    /* Weather Name */
    stClock.weather_name = lv_label_create(img_now, NULL);
    lv_obj_add_style(stClock.weather_name, LV_LABEL_PART_MAIN, &weather_name_style);

    lv_obj_align(stClock.weather, img_now, LV_ALIGN_IN_TOP_MID, IMG_NOW_IN_TOP_MID_X, IMG_NOW_IN_TOP_MID_Y);
    lv_obj_align(stClock.weather_name, img_now, LV_ALIGN_IN_BOTTOM_MID, IMG_NOW_IN_BOTTOM_MID_X, IMG_NOW_IN_BOTTOM_MID_Y);

    /* Temp & Humi */
    lv_obj_t *temp_obj = lv_obj_create(weather_now, NULL);
    lv_obj_set_click(temp_obj, false);
    lv_obj_set_size(temp_obj, IMG_NOW_TEMP_W, IMG_NOW_TEMP_H);
    lv_obj_align(temp_obj, weather_now, LV_ALIGN_IN_TOP_LEFT, IMG_NOW_TEMP_ALIGN_X, IMG_NOW_TEMP_ALIGN_Y);
    lv_obj_add_style(temp_obj, LV_OBJ_PART_MAIN, &img_style);

    /* Location */
    stClock.location = lv_label_create(temp_obj, NULL);
    lv_obj_add_style(stClock.location, LV_LABEL_PART_MAIN, &location_label_style);

    stClock.temp_img = lv_img_create(temp_obj, NULL);
    lv_img_set_src(stClock.temp_img, &temp_img);

    stClock.temp = lv_label_create(temp_obj, NULL);
    lv_obj_add_style(stClock.temp, LV_LABEL_PART_MAIN, &humi_label_style);

    stClock.humi_img = lv_img_create(temp_obj, NULL);
    lv_img_set_src(stClock.humi_img, &humi_img);

    stClock.humi = lv_label_create(temp_obj, NULL);
    lv_obj_add_style(stClock.humi, LV_LABEL_PART_MAIN, &humi_label_style);    

    lv_obj_align(stClock.location, temp_obj, LV_ALIGN_IN_BOTTOM_RIGHT, IMG_NOW_IN_LOCATION_BOTTOM_RIGHT_X, 
            IMG_NOW_IN_LOCATION_BOTTOM_RIGHT_Y);
    lv_obj_align(stClock.temp_img, temp_obj, LV_ALIGN_IN_TOP_LEFT, IMG_NOW_TEMP_ALIGN_IN_TOP_LEFT_X, 
            IMG_NOW_TEMP_ALIGN_IN_TOP_LEFT_Y);
    lv_obj_align(stClock.temp, temp_obj, LV_ALIGN_IN_BOTTOM_LEFT, IMG_NOW_TEMP_ALIGN_IN_BOTTOM_LEFT_X, 
            IMG_NOW_TEMP_ALIGN_IN_BOTTOM_LEFT_Y);
    lv_obj_align(stClock.humi_img, temp_obj, LV_ALIGN_IN_TOP_RIGHT, IMG_NOW_TEMP_ALIGN_IN_TOP_RIGHT_X,
            IMG_NOW_TEMP_ALIGN_IN_TOP_RIGHT_Y);
    lv_obj_align(stClock.humi, temp_obj, LV_ALIGN_IN_BOTTOM_RIGHT, IMG_NOW_TEMP_ALIGN_IN_BOTTOM_RIGHT_X,
            IMG_NOW_TEMP_ALIGN_IN_BOTTOM_RIGHT_Y);


	/* Weather Forecast Display */
	lv_obj_t *img_forecast = lv_obj_create(weather_forecast, NULL);
	lv_obj_set_click(img_forecast, false);
	lv_obj_set_size(img_forecast, IMG_FORECAST_W, IMG_FORECAST_H);
	lv_obj_align(img_forecast, weather_forecast, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(img_forecast, LV_OBJ_PART_MAIN, &img_style);

	stForecastInfo[0].date = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[0].date, LV_LABEL_PART_MAIN, &date_label_style);

	stForecastInfo[0].weather = lv_img_create(img_forecast, NULL);
	lv_img_set_src(stForecastInfo[0].weather, (const lv_img_dsc_t*)lv_weather[0].img_dsc);

	stForecastInfo[0].weather_name = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[0].weather_name, LV_LABEL_PART_MAIN, &location_label_style);

	stForecastInfo[0].temp = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[0].temp, LV_LABEL_PART_MAIN, &humi_label_style);

	stForecastInfo[1].date = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[1].date, LV_LABEL_PART_MAIN, &date_label_style);

	stForecastInfo[1].weather = lv_img_create(img_forecast, NULL);
	lv_img_set_src(stForecastInfo[1].weather, (const lv_img_dsc_t*)lv_weather[0].img_dsc);

	stForecastInfo[1].weather_name = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[1].weather_name, LV_LABEL_PART_MAIN, &location_label_style);

	stForecastInfo[1].temp = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[1].temp, LV_LABEL_PART_MAIN, &humi_label_style);

	stForecastInfo[2].date = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[2].date, LV_LABEL_PART_MAIN, &date_label_style);

	stForecastInfo[2].weather = lv_img_create(img_forecast, NULL);
	lv_img_set_src(stForecastInfo[2].weather, (const lv_img_dsc_t*)lv_weather[0].img_dsc);

	stForecastInfo[2].weather_name = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[2].weather_name, LV_LABEL_PART_MAIN, &location_label_style);

	stForecastInfo[2].temp = lv_label_create(img_forecast, NULL);
	lv_obj_add_style(stForecastInfo[2].temp, LV_LABEL_PART_MAIN, &humi_label_style);

	lv_obj_align(stForecastInfo[0].date, img_forecast, 
            LV_ALIGN_IN_TOP_LEFT, IMG_FORECAST_DATE_IN_TOP_LEFT_X, IMG_FORECAST_DATE_IN_TOP_LEFT_Y);
	lv_obj_align(stForecastInfo[0].weather, img_forecast, 
            LV_ALIGN_IN_TOP_LEFT, IMG_FORECAST_IN_TOP_LEFT_X, IMG_FORECAST_IN_TOP_LEFT_Y);
	lv_obj_align(stForecastInfo[0].weather_name, img_forecast, 
            LV_ALIGN_IN_LEFT_MID, IMG_FORECAST_IN_LEFT_MID_X, IMG_FORECAST_IN_LEFT_MID_Y);
	lv_obj_align(stForecastInfo[0].temp, img_forecast, 
            LV_ALIGN_IN_BOTTOM_LEFT, IMG_FORECAST_IN_BOTTOM_LEFT_X, IMG_FORECAST_IN_BOTTOM_LEFT_Y);

	lv_obj_align(stForecastInfo[1].date, img_forecast, 
            LV_ALIGN_IN_TOP_MID, IMG_FORECAST_DATE_IN_TOP_MID_X, IMG_FORECAST_DATE_IN_TOP_MID_Y);
	lv_obj_align(stForecastInfo[1].weather, img_forecast, 
            LV_ALIGN_IN_TOP_MID, IMG_FORECAST_IN_TOP_MID_X, IMG_FORECAST_IN_TOP_MID_Y);
	lv_obj_align(stForecastInfo[1].weather_name, img_forecast, 
            LV_ALIGN_CENTER, IMG_FORECAST_CENTER_X, IMG_FORECAST_CENTER_Y);
	lv_obj_align(stForecastInfo[1].temp, img_forecast, 
            LV_ALIGN_IN_BOTTOM_MID, IMG_FORECAST_IN_BOTTOM_MID_X, IMG_FORECAST_IN_BOTTOM_MID_Y);

	lv_obj_align(stForecastInfo[2].date, img_forecast, 
            LV_ALIGN_IN_TOP_RIGHT, IMG_FORECAST_DATE_IN_TOP_RIGHT_X, IMG_FORECAST_DATE_IN_TOP_RIGHT_Y);
	lv_obj_align(stForecastInfo[2].weather, img_forecast, 
            LV_ALIGN_IN_TOP_RIGHT, IMG_FORECAST_IN_TOP_RIGHT_X, IMG_FORECAST_IN_TOP_RIGHT_Y);
	lv_obj_align(stForecastInfo[2].weather_name, img_forecast, 
            LV_ALIGN_IN_RIGHT_MID, IMG_FORECAST_IN_RIGHT_MID_X, IMG_FORECAST_IN_RIGHT_MID_Y);
	lv_obj_align(stForecastInfo[2].temp, img_forecast, 
            LV_ALIGN_IN_BOTTOM_RIGHT, IMG_FORECAST_IN_BOTTOM_RIGHT_X, IMG_FORECAST_IN_BOTTOM_RIGHT_Y);

	/* Time & Date */
	lv_obj_t *time_obj = lv_obj_create(pstWall, NULL);
	lv_obj_set_click(time_obj, false);
	lv_obj_set_size(time_obj, TIME_DATE_W, TIME_DATE_H);
	lv_obj_align(time_obj, pstWall, LV_ALIGN_CENTER, TIME_DATE_ALIGN_CENTER_X, TIME_DATE_ALIGN_CENTER_Y);
	lv_obj_add_style(time_obj, LV_OBJ_PART_MAIN, &time_style);

    /*Clock display*/
    lv_obj_t *clock_obj = lv_obj_create(time_obj, NULL);
    lv_obj_set_size(clock_obj, CLOCK_WIDTH, CLOCK_HEIGHT);
    lv_obj_set_pos(clock_obj, CLOCK_POS_X, CLOCK_POS_Y);
    lv_obj_add_style(clock_obj, LV_OBJ_PART_MAIN, &clock_style);

    stClock.clock_label = lv_label_create(clock_obj, NULL);
    lv_obj_add_style(stClock.clock_label, LV_LABEL_PART_MAIN, &clock_label_style);

    /*Date display*/
    lv_obj_t *date_obj = lv_obj_create(time_obj, NULL);
    lv_obj_set_size(date_obj, DATE_WIDTH, DATE_HEIGHT);
    lv_obj_set_pos(date_obj, DATE_POS_X, DATE_POS_Y);
    lv_obj_add_style(date_obj, LV_OBJ_PART_MAIN, &date_style);

    stClock.date_label = lv_label_create(date_obj, NULL);
    lv_obj_add_style(stClock.date_label, LV_LABEL_PART_MAIN, &date_label_style);

    /*Week display*/
    stClock.week_label = lv_label_create(date_obj, NULL);
    lv_obj_add_style(stClock.week_label, LV_LABEL_PART_MAIN, &week_lable_style);

    lv_obj_align(stClock.clock_label, clock_obj, LV_ALIGN_CENTER, CLOCK_LABEL_ALIGN_CENTER_X, CLOCK_LABEL_ALIGN_CENTER_Y);
    lv_obj_align(stClock.date_label, date_obj, LV_ALIGN_IN_TOP_MID, DATE_LABEL_IN_TOP_MID_X, DATE_LABEL_IN_TOP_MID_Y);
    lv_obj_align(stClock.week_label, date_obj, LV_ALIGN_IN_BOTTOM_MID, WEEK_LABEL_IN_BOTTOM_MID_X, WEEK_LABEL_IN_BOTTOM_MID_Y);

    pstTask = lv_task_create(clock_task, 200, LV_TASK_PRIO_MID, NULL);
}

void lv_clock_now(LV_CLOCK_TIME_S time, LV_CLOCK_WEATHER_S weather)
{
    stTime.year = time.year;
    stTime.mon = time.mon;
    stTime.mday = time.mday;
    stTime.wday = time.wday;
    stTime.hour = time.hour;
    stTime.min = time.min;
    stTime.sec = time.sec;

    sprintf(stWeather.location, "%s", weather.location);
    stWeather.code = weather.code;
    stWeather.temp = weather.temp;
    stWeather.humi = weather.humi;
}

void lv_clock_forecast(LV_CLOCK_FORECAST_S *forecast)
{
    memcpy(stForecast, forecast, sizeof(stForecast));
}


#ifdef __cplusplus
} /* extern "C" */
#endif

