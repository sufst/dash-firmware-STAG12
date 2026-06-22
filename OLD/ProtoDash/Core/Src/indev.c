/*
 * indev.c
 *
 *  Created on: Aug 28, 2025
 *      Author: Adam
 */
#include "lvgl.h"
#include "screens.h"
#include "xpt2046.h"
#include "indev.h"
#include <stdio.h>


//Static Functions

static void ConvXPTtoILI(uint16_t *x, uint16_t *y)
{
	int16_t tx,ty;
	tx = (int16_t)(((int32_t)*x - XPT_XMIN) * GUI_WIDTH / XPT_WIDTH);
	tx = (tx < 0) ? 0 : tx;
	tx = (tx >= GUI_WIDTH) ? GUI_WIDTH-1 : tx;
	ty = (int16_t)(((int32_t)*y - XPT_YMIN) * GUI_HEIGHT / XPT_HEIGHT);

	//Adding fix to mirror Y axis (due to LCD_ORIENTATION_LANDSCAPE_MIRROR)
	ty = GUI_HEIGHT - 1 - ty;

	ty = (ty < 0) ? 0 : ty;
	ty = (ty >= GUI_HEIGHT) ? GUI_HEIGHT-1 : ty;
	*x = tx;
	*y = ty;
}

struct {
	lv_coord_t x;
	lv_coord_t y;
}get_xy;


//Touchpad

void touch_init(void)
{
	XPT2046_Init();

	lv_indev_t * touch = lv_indev_create();
	lv_indev_set_type(touch, LV_INDEV_TYPE_POINTER);
	lv_indev_set_read_cb(touch, touch_read_cb);
}

void touch_read_cb(lv_indev_t * indev, lv_indev_data_t * data)
{
	static lv_coord_t last_x = 0;
	static lv_coord_t last_y = 0;

	if(touchpad_is_pressed())
	{

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
		//lv_label_set_text(objects.detected, "YES" );
		last_x = get_xy.x;
		last_y = get_xy.y;

		char buf[32];
		sprintf(buf, "%03lu", last_x);
		//lv_label_set_text(objects.xpos, buf);
		sprintf(buf, "%03lu", last_y);
		//lv_label_set_text(objects.ypos, buf);
	    data->state = LV_INDEV_STATE_PR;
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
		//lv_label_set_text(objects.detected, "NO" );
		data->state = LV_INDEV_STATE_REL;
	}

	/*Set the last pressed coordinates*/
	data->point.x = last_x;
	data->point.y = last_y;
}

bool touchpad_is_pressed(void)
{

	static uint16_t prevx = GUI_WIDTH;
	static uint16_t prevy = GUI_HEIGHT;
	uint16_t intx, inty;
	XPT2046_Update(&intx, &inty);
	if (XPT2046_IsReasonable(intx, inty))
	{
		ConvXPTtoILI(&intx, &inty);
		if (intx != prevx || inty != prevy)
		{
			prevx = intx;
			prevy = inty;
			get_xy.x = (lv_coord_t )intx;
			get_xy.y = (lv_coord_t )inty;
			return true;
		}
	}
	return false;
}

