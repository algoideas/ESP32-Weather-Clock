/*********************
 *      INCLUDES
 *********************/
#include "lv_gui.h"
#include "lv_clock.h"

#ifdef __cplusplus
extern "C" {
#endif

static lv_obj_t *load_arc;

static void load_task(lv_task_t *t)
{
    static int16_t a = 0;

    a += 5;
    lv_arc_set_end_angle(load_arc, a);
    if (a >= 360)
    {
        lv_clock();
        lv_task_del(t);
        return;
    }
}

void lv_gui(void)
{ 
    lv_obj_t *scr = lv_scr_act();
    lv_obj_clean_style_list(scr, LV_OBJ_PART_MAIN);
    lv_obj_set_style_local_bg_opa(scr, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_OPA_COVER);
    lv_obj_set_style_local_bg_color(scr, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_BLACK);
    lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);

    /* ui */
    static lv_style_t style_arc_bg;
    static lv_style_t style_arc_indic;

    load_arc = lv_arc_create(scr, NULL);
    lv_arc_set_start_angle(load_arc, 0);
    lv_arc_set_end_angle(load_arc, 0);
    lv_arc_set_bg_angles(load_arc, 0, 360);
    lv_arc_set_rotation(load_arc, 270);

    lv_obj_set_size(load_arc, 180, 180);
    lv_obj_set_click(load_arc, false);
    lv_obj_align(load_arc, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_style_init(&style_arc_indic);
    lv_style_set_line_width(&style_arc_indic, LV_STATE_DEFAULT, 4);
    lv_style_set_line_color(&style_arc_indic, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    lv_style_init(&style_arc_bg);
    lv_style_set_bg_color(&style_arc_bg, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_line_width(&style_arc_bg, LV_STATE_DEFAULT, 4);
    lv_style_set_line_color(&style_arc_bg, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_width(&style_arc_bg, LV_STATE_DEFAULT, 0);

    lv_style_set_value_font(&style_arc_bg, LV_STATE_DEFAULT, &lv_font_montserrat_16);
    lv_style_set_value_color(&style_arc_bg, LV_STATE_DEFAULT, LV_COLOR_CYAN);
    lv_style_set_value_align(&style_arc_bg, LV_STATE_DEFAULT, LV_ALIGN_CENTER);
    lv_obj_set_style_local_value_str(load_arc, LV_ARC_PART_BG, LV_STATE_DEFAULT, "Loading");

    lv_obj_add_style(load_arc, LV_ARC_PART_INDIC, &style_arc_indic);
    lv_obj_add_style(load_arc, LV_ARC_PART_BG, &style_arc_bg);
    lv_task_create(load_task, 20, LV_TASK_PRIO_LOWEST, load_arc);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

