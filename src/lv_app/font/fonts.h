#ifndef FONTS_H_
#define FONTS_H_

#include "lvgl.h"

struct LV_FONT
{
    char *name_en;
    char *name;
};

extern const struct LV_FONT lv_font[40];

LV_FONT_DECLARE(weather_font);
LV_FONT_DECLARE(humiture_font);
LV_FONT_DECLARE(week_font);

#endif