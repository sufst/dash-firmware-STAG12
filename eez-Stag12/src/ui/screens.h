#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    _SCREEN_ID_LAST = 1
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *pdm_10;
    lv_obj_t *vcu_state;
    lv_obj_t *inv_state;
    lv_obj_t *obj0;
    lv_obj_t *wheel_fl;
    lv_obj_t *wheel_fl_1;
    lv_obj_t *pdm_11;
    lv_obj_t *apps;
    lv_obj_t *bps;
    lv_obj_t *inverter_temp;
    lv_obj_t *inverter_temp_1;
    lv_obj_t *inverter_temp_2;
    lv_obj_t *inverter_temp_3;
    lv_obj_t *inverter_temp_4;
    lv_obj_t *inverter_temp_5;
    lv_obj_t *inverter_temp_6;
    lv_obj_t *inverter_temp_7;
    lv_obj_t *inverter_temp_8;
    lv_obj_t *inverter_temp_9;
    lv_obj_t *inverter_temp_10;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/