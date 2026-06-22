#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *bms_pack_current;
    lv_obj_t *bms_pack_voltage;
    lv_obj_t *bms_soc;
    lv_obj_t *bms_hi_temp;
    lv_obj_t *bms_lo_temp;
    lv_obj_t *bms_avg_temp;
    lv_obj_t *bms_int_temp;
    lv_obj_t *vcu_ctrl_state;
    lv_obj_t *vcu_pump_enable;
    lv_obj_t *vcu_fan_enable;
    lv_obj_t *button1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/