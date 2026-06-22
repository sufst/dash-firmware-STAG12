/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "screens.h"
#include "usart.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
QueueHandle_t xCanTx;
QueueHandle_t xCanRx;
SemaphoreHandle_t xCanDataMutex;
/* USER CODE END Variables */
/* Definitions for GUITask */
osThreadId_t GUITaskHandle;
const osThreadAttr_t GUITask_attributes = {
  .name = "GUITask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CANRxTask */
osThreadId_t CANRxTaskHandle;
const osThreadAttr_t CANRxTask_attributes = {
  .name = "CANRxTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for CANTxTask */
osThreadId_t CANTxTaskHandle;
const osThreadAttr_t CANTxTask_attributes = {
  .name = "CANTxTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Heartbeat */
osThreadId_t HeartbeatHandle;
const osThreadAttr_t Heartbeat_attributes = {
  .name = "Heartbeat",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
static uint16_t decode16(const uint8_t *data, uint8_t start_byte);
/* USER CODE END FunctionPrototypes */

void StartGUITask(void *argument);
void StartCANRxTask(void *argument);
void StartCANTxTask(void *argument);
void StartHeartbeat(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
	xCanDataMutex = xSemaphoreCreateMutex();
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */

	xCanRx = xQueueCreate(32, sizeof(CANMessage_t));
	xCanTx = xQueueCreate(16, sizeof(CANMessage_t));

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of GUITask */
  GUITaskHandle = osThreadNew(StartGUITask, NULL, &GUITask_attributes);

  /* creation of CANRxTask */
  CANRxTaskHandle = osThreadNew(StartCANRxTask, NULL, &CANRxTask_attributes);

  /* creation of CANTxTask */
  CANTxTaskHandle = osThreadNew(StartCANTxTask, NULL, &CANTxTask_attributes);

  /* creation of Heartbeat */
  HeartbeatHandle = osThreadNew(StartHeartbeat, NULL, &Heartbeat_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartGUITask */
/**
  * @brief  Function implementing the GUITask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartGUITask */
void StartGUITask(void *argument)
{
  /* USER CODE BEGIN StartGUITask */
  /* Infinite loop */
  for(;;)
  {
	  //lock access to shared data
	  xSemaphoreTake(xCanDataMutex, portMAX_DELAY);

	  //take snapshot of data and calculate factors
	  uint16_t current = dashboardData.BMS_Pack_Current * 0.1;
	  uint16_t voltage = dashboardData.BMS_Pack_Inst_voltage * 0.1;
	  uint8_t soc = dashboardData.BMS_Pack_SOC * 0.5;
	  uint8_t hi_temp = dashboardData.BMS_High_Temperature;
	  uint8_t lo_temp = dashboardData.BMS_Low_Temperature;
	  uint8_t avg_temp = dashboardData.BMS_Average_Temperature;
	  uint8_t int_temp = dashboardData.BMS_Internal_Temperature;
	  uint8_t vcu_state = dashboardData.VCU_CTRL_State;
	  uint8_t vcu_fan = dashboardData.VCU_Fan_Enable;
	  uint8_t vcu_pump = dashboardData.VCU_Pump_Enable;

	  //unlock shared data
	  xSemaphoreGive(xCanDataMutex);

	  //Update GUI objects with formatted text
	  char buf[32];

	  sprintf(buf, "%03uA", current);
	  lv_label_set_text(objects.bms_pack_current, buf);
	  sprintf(buf, "%03uV", voltage);
	  lv_label_set_text(objects.bms_pack_voltage, buf);
	  sprintf(buf, "%02u%%", soc);
	  lv_label_set_text(objects.bms_soc, buf);
	  sprintf(buf, "%02u°C", hi_temp);
	  lv_label_set_text(objects.bms_hi_temp, buf);
	  sprintf(buf, "%02u°C", lo_temp);
	  lv_label_set_text(objects.bms_lo_temp, buf);
	  sprintf(buf, "%02u°C", avg_temp);
	  lv_label_set_text(objects.bms_avg_temp, buf);
	  sprintf(buf, "%02u°C", int_temp);
	  lv_label_set_text(objects.bms_int_temp, buf);
	  sprintf(buf, "%1u", vcu_state);
	  lv_label_set_text(objects.vcu_ctrl_state, buf);
	  sprintf(buf, "%1u", vcu_fan);
	  lv_label_set_text(objects.vcu_fan_enable, buf);
	  sprintf(buf, "%1u", vcu_pump);
	  lv_label_set_text(objects.vcu_pump_enable, buf);

	  //LVGL Housekeeping
	  lv_timer_handler_run_in_period(5);

	  //Give RTOS time to do other tasks
	  vTaskDelay(pdMS_TO_TICKS(50));  // update GUI every 50ms
  }
  /* USER CODE END StartGUITask */
}

/* USER CODE BEGIN Header_StartCANRxTask */
/**
* @brief Function implementing the CANRxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCANRxTask */
void StartCANRxTask(void *argument)
{
  /* USER CODE BEGIN StartCANRxTask */
	  if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) // Activate Rx message interrupt
	  {
		  Error_Handler();
	  }

	  CANMessage_t msg;
  /* Infinite loop */
  for(;;)
  {
    if(xQueueReceive(xCanRx, &msg, portMAX_DELAY) == pdPASS)
    {

    	xSemaphoreTake(xCanDataMutex, portMAX_DELAY);
    	//Parse CAN messages and update shared data
    	switch(msg.id)
    	{
    	case 0x201:
    				dashboardData.BMS_Pack_Current = decode16(msg.data, 1);      // Start bit 8, 16 bits
    				dashboardData.BMS_Pack_Inst_voltage = decode16(msg.data, 3); // Start bit 24, 16 bits
    				dashboardData.BMS_Pack_SOC = msg.data[4]; 					 // Start bit 32, 8 bits
    				break;
    	case 0x202:
    				dashboardData.BMS_High_Temperature = msg.data[0];    		 // Start bit 0, 8 bits
    				dashboardData.BMS_Low_Temperature = msg.data[1];    		 // Start bit 8, 8 bits
    				dashboardData.BMS_Average_Temperature = msg.data[2];		 // Start bit 16, 8 bits
    				dashboardData.BMS_Internal_Temperature = msg.data[3]; 		 // Start bit 24, 8 bits
    				break;
    	case 0x104:
    				dashboardData.VCU_Inverter_Enable = msg.data[0];			 // Start bit 0, 8 bits
    				dashboardData.VCU_Pump_Enable = msg.data[1];				 // Start bit 8, 8 bits
    				dashboardData.VCU_Fan_Enable = msg.data[3];					 // Start bit 24, 8 bits
    				break;
    	case 0x101:
    				dashboardData.VCU_CTRL_State = msg.data[2]; 				 //Start bit 16, 8 bits
    				dashboardData.VCU_Power_saving = msg.data[3] >> 3; 			 //Start bit 27, 1 bit
    				break;
    	}
    	xSemaphoreGive(xCanDataMutex);
    }
  }
  /* USER CODE END StartCANRxTask */
}

/* USER CODE BEGIN Header_StartCANTxTask */
/**
* @brief Function implementing the CANTxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCANTxTask */
void StartCANTxTask(void *argument)
{
  /* USER CODE BEGIN StartCANTxTask */
	CANMessage_t msg;
  /* Infinite loop */
  for(;;)
  {
	  if(xQueueReceive(xCanTx, &msg, portMAX_DELAY) == pdPASS)
	  {
		  SendCANMessage(&msg);
	  }

  }
  /* USER CODE END StartCANTxTask */
}

/* USER CODE BEGIN Header_StartHeartbeat */
/**
* @brief Function implementing the Heartbeat thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartHeartbeat */
void StartHeartbeat(void *argument)
{
  /* USER CODE BEGIN StartHeartbeat */
  /* Infinite loop */
    CANMessage_t msg = {
        .id = 0x001,
        .dlc = 8,
        .data = {0}
    };

  for(;;)
  {
    osDelay(pdMS_TO_TICKS(1000));
    xQueueSend(xCanTx, &msg, portMAX_DELAY);
    msg.data[0] ^= 1;
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

    char tmsg[] = "Hello from Xbee!\r\n";
    HAL_UART_Transmit(&huart4, (uint8_t*)tmsg, strlen(tmsg), HAL_MAX_DELAY);
  }
  /* USER CODE END StartHeartbeat */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
static uint16_t decode16(const uint8_t *data, uint8_t start_byte)
{
    return (data[start_byte] << 8) | data[start_byte + 1];
}
/* USER CODE END Application */

