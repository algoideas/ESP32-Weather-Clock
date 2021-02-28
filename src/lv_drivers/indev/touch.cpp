#include "touch.h"
#include "lvgl.h"
#include "base.h"
#if USE_TOUCH
#include <TFT_Touch.h>
#endif

#if USE_TOUCH
/* Touch Pin */
#define DOUT 13  /* Data out pin (T_DO) of touch screen */
#define DIN  12  /* Data in pin (T_DIN) of touch screen */
#define DCS  15  /* Chip select pin (T_CS) of touch screen */
#define DCLK 14  /* Clock pin (T_CLK) of touch screen */

/* Create an instance of the touch screen library */
TFT_Touch tc = TFT_Touch(DCS, DCLK, DIN, DOUT);
#endif

static bool touch_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
#if USE_TOUCH
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;

    bool touched = tc.Pressed();
    if (touched)
    {
        last_x = (320 - tc.X());
        last_y = (240 - tc.Y());
        data->state = LV_INDEV_STATE_PR; 
        
        Serial.print("Data x");
        Serial.println(last_x);

        Serial.print("Data y");
        Serial.println(last_y);
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Set the coordinates (if released use the last pressed coordinates)*/
    data->point.x = last_x;
    data->point.y = last_y;
#endif

    return false; /*Return `false` because we are not buffering and no more data to read*/
}

void Touch::init()
{
#if USE_TOUCH
    tc.setCal(481, 3395, 755, 3487, 320, 240, 1);
    tc.setRotation(3);
#endif

    /*Initialize the input device driver*/
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;     /*Touchpad is a pointer-like device*/
    indev_drv.read_cb = touch_read;
    lv_indev_drv_register(&indev_drv);
}

