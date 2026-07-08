/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "can.h"

/* USER CODE BEGIN 0 */
#include "cmsis_os2.h"
#include "rtcan.h"

#ifndef CAN_BUS_S_THREAD_PRIORITY
#define CAN_BUS_S_THREAD_PRIORITY ((uint32_t) osPriorityAboveNormal)
#endif
#ifndef CAN_BUS_T_THREAD_PRIORITY
#define CAN_BUS_T_THREAD_PRIORITY ((uint32_t) osPriorityAboveNormal)
#endif
#ifndef CAN_BUS_TX_THREAD_STACK_SIZE
#define CAN_BUS_TX_THREAD_STACK_SIZE (512U * 4U)
#endif
#ifndef CAN_BUS_RX_THREAD_STACK_SIZE
#define CAN_BUS_RX_THREAD_STACK_SIZE (512U * 4U)
#endif
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 6;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = ENABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_TX_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_TX_IRQn);
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN2_SCE_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_SCE_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_6);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN2_SCE_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

#define CAN_BUS_CAN1_FILTER_BANK        0U
#define CAN_BUS_CAN2_FILTER_BANK        14U
#define CAN_BUS_SLAVE_START_FILTER_BANK 14U

rtcan_handle_t can_bus_rtcan_s;
rtcan_handle_t can_bus_rtcan_t;

static rtcan_status_t init_one_bus(rtcan_handle_t *rtcan_h,
                                   CAN_HandleTypeDef *hcan,
                                   uint32_t thread_priority)
{
    if ((rtcan_h == NULL) || (hcan == NULL))
    {
        return RTCAN_ERROR;
    }

    const uint32_t filter_bank = (hcan->Instance == CAN1)
                                      ? CAN_BUS_CAN1_FILTER_BANK
                                      : CAN_BUS_CAN2_FILTER_BANK;

    const CAN_FilterTypeDef filter = {
        .FilterIdHigh = 0x0000,
        .FilterIdLow = 0x0000,
        .FilterMaskIdHigh = 0x0000,
        .FilterMaskIdLow = 0x0000,
        .FilterFIFOAssignment = CAN_FILTER_FIFO0,
        .FilterBank = filter_bank,
        .FilterMode = CAN_FILTERMODE_IDMASK,
        .FilterScale = CAN_FILTERSCALE_32BIT,
        .FilterActivation = CAN_FILTER_ENABLE,
        .SlaveStartFilterBank = CAN_BUS_SLAVE_START_FILTER_BANK,
    };

    const rtcan_config_t config = {
        .thread_priority = thread_priority,
        .tx_thread_stack_size = CAN_BUS_TX_THREAD_STACK_SIZE,
        .rx_thread_stack_size = CAN_BUS_RX_THREAD_STACK_SIZE,
        .tx_thread_stack_mem = NULL,
        .rx_thread_stack_mem = NULL,
        .filters = &filter,
        .filter_count = 1U,
    };

    rtcan_status_t status = rtcan_init(rtcan_h, hcan, &config);
    if (status == RTCAN_OK)
    {
        status = rtcan_start(rtcan_h);
    }
    return status;
}

rtcan_status_t can_bus_init(CAN_HandleTypeDef *can_s_h, CAN_HandleTypeDef *can_t_h)
{
    if ((can_s_h == NULL) || (can_t_h == NULL) || (can_s_h->Instance == can_t_h->Instance))
    {
        return RTCAN_ERROR;
    }

    rtcan_status_t s_status = init_one_bus(&can_bus_rtcan_s, can_s_h, CAN_BUS_S_THREAD_PRIORITY);
    rtcan_status_t t_status = init_one_bus(&can_bus_rtcan_t, can_t_h, CAN_BUS_T_THREAD_PRIORITY);

    return ((s_status == RTCAN_OK) && (t_status == RTCAN_OK)) ? RTCAN_OK : RTCAN_ERROR;
}

uint32_t can_bus_get_error(void)
{
    uint32_t s_err = rtcan_get_error(&can_bus_rtcan_s);
    uint32_t t_err = rtcan_get_error(&can_bus_rtcan_t);
    return (s_err & 0x0000FFFFU) | ((t_err & 0x0000FFFFU) << 16);
}

static rtcan_handle_t *dispatch_target(const CAN_HandleTypeDef *hcan)
{
    if (hcan == NULL) return NULL;
    if (hcan == can_bus_rtcan_s.hcan) return &can_bus_rtcan_s;
    if (hcan == can_bus_rtcan_t.hcan) return &can_bus_rtcan_t;
    return NULL;
}

static void handle_tx_event(CAN_HandleTypeDef *hcan)
{
    rtcan_handle_t *rtcan_h = dispatch_target(hcan);
    if (rtcan_h != NULL) (void) rtcan_handle_tx_mailbox_callback(rtcan_h, hcan);
}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan) { handle_tx_event(hcan); }
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan) { handle_tx_event(hcan); }
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan) { handle_tx_event(hcan); }

void HAL_CAN_TxMailbox0AbortCallback(CAN_HandleTypeDef *hcan) { handle_tx_event(hcan); }
void HAL_CAN_TxMailbox1AbortCallback(CAN_HandleTypeDef *hcan) { handle_tx_event(hcan); }
void HAL_CAN_TxMailbox2AbortCallback(CAN_HandleTypeDef *hcan) { handle_tx_event(hcan); }

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    rtcan_handle_t *rtcan_h = dispatch_target(hcan);
    if (rtcan_h != NULL) (void) rtcan_handle_rx_it(rtcan_h, hcan, CAN_RX_FIFO0);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    rtcan_handle_t *rtcan_h = dispatch_target(hcan);
    if (rtcan_h != NULL) (void) rtcan_handle_rx_it(rtcan_h, hcan, CAN_RX_FIFO1);
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
    rtcan_handle_t *rtcan_h = dispatch_target(hcan);
    if (rtcan_h != NULL) (void) rtcan_handle_hal_error(rtcan_h, hcan);
}

/* USER CODE END 1 */
