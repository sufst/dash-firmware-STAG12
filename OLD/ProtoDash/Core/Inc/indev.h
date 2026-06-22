/*
 * indev.h
 *
 *  Created on: Aug 28, 2025
 *      Author: Adam
 */

#ifndef INC_INDEV_H_
#define INC_INDEV_H_

#include "main.h"
#include "ili9341.h"

#define GUI_WIDTH  ILI9341_PIXEL_WIDTH
#define GUI_HEIGHT ILI9341_PIXEL_HEIGHT


void touch_init();
void touch_read_cb(lv_indev_t * indev, lv_indev_data_t * data);
bool touchpad_is_pressed(void);

#endif /* INC_INDEV_H_ */
