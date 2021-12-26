#include "display.h"

#define TFT_E_SPI 1
#ifdef TFT_E_SPI
#include <TFT_eSPI.h>
#include <SPI.h>
#endif

#define TFT_BL 21

/*
TFT pins should be set in path .pio/libdeps/esp32dev/TFT_eSPI/User_Setups/Setup1_ILI9341.h
*/
/* TFT */
TFT_eSPI tft = TFT_eSPI();

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

/* default resolution */
static int width = 320;
static int height = 240;

#if LV_USE_LOG
static void disp_print(lv_log_level_t level, const char* file, uint32_t line, const char* fun, const char* dsc)
{
	Serial.printf("%s@%d %s->%s\r\n", file, line, fun, dsc);
	Serial.flush();
}
#endif

static void disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
	uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite(); /* Start new TFT transaction */
	tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite(); /* terminate TFT transaction */

	lv_disp_flush_ready(disp);
}

void Display::init()
{
	lv_init();

#if LV_USE_LOG
	lv_log_register_print_cb(disp_print); /* register print function for debugging */
#endif

    ledcSetup(10, 5000/*freq*/, 10 /*resolution*/);
    ledcAttachPin(TFT_BL, 10);
    analogReadResolution(10);
    ledcWrite(10, 1023);

#ifdef TFT_E_SPI
    tft.begin(); /* TFT init */

    /*
     * Screen orientation:
     *  0 - "Portrait"
     *  1 - "Landscape"
     *  2 - "Portrait Inverted"
     *  3 - "Landscape Inverted"
     */
    tft.setRotation(1);  
    tft.fillScreen(BLACK);
#else
    uint16_t identifier = 0x0;

    tft.fillScreen(BLACK);
    tft.reset();

    identifier = tft.readID();
    if (identifier == 0x9341) {
        width = 320;
        height = 240;
        Serial.println(F("Found ILI9341 LCD driver"));
    } else if (identifier == 0x9486) {     
        width = 480;
        height = 320;
        Serial.println(F("Found ILI9486 LCD driver"));
    } else {
        Serial.print(F("Unknown LCD driver chip: "));
        Serial.println(identifier, HEX);
        identifier = 0x9341;
        width = 320;
        height = 240;
    }

    tft.begin(identifier);
    tft.setRotation(1);  
    tft.fillScreen(BLACK);
#endif

	lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

	/*Initialize the display*/
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.hor_res = width;
	disp_drv.ver_res = height;
	disp_drv.flush_cb = disp_flush;
	disp_drv.buffer = &disp_buf;
	lv_disp_drv_register(&disp_drv);
}

void Display::routine()
{
	lv_task_handler();
}

