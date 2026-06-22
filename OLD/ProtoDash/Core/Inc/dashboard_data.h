/*
 * dashboard_data.h
 *
 *  Created on: Aug 27, 2025
 *      Author: Adam
 */

#ifndef INC_DASHBOARD_DATA_H_
#define INC_DASHBOARD_DATA_H_

#include "main.h"

typedef struct
{
	uint16_t BMS_Pack_Current;
	uint16_t BMS_Pack_Inst_voltage;
	uint8_t BMS_Pack_SOC;
	uint8_t BMS_High_Temperature;
	uint8_t BMS_Low_Temperature;
	uint8_t BMS_Average_Temperature;
	uint8_t BMS_Internal_Temperature;

	uint8_t VCU_Inverter_Enable;
	uint8_t VCU_Pump_Enable;
	uint8_t VCU_Fan_Enable;

	uint8_t VCU_CTRL_State;
	uint8_t VCU_Power_saving;
} DashboardData_t;

//declare as shared variable for multiple files
extern DashboardData_t dashboardData;

#endif /* INC_DASHBOARD_DATA_H_ */
