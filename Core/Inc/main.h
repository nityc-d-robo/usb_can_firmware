/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define MASTER_ID 0x60

#define CAN_TX_SIZE 8
#define CAN_RX_SIZE 8
#define CAN_RINGBUF_SIZE 256
#define USB_RINGBUF_SIZE 64
#define USB_RX_SIZE 11
#define USB_TX_SIZE 8

typedef struct {
  CAN_RxHeaderTypeDef header;
  uint8_t data[CAN_RX_SIZE];
} CanFrame;

typedef struct {
  CanFrame buf[CAN_RINGBUF_SIZE];
  uint16_t write_idx;
  uint16_t read_idx;
} CanRingBuf;

typedef struct {
  uint8_t buf[USB_RINGBUF_SIZE][USB_RX_SIZE];
  uint16_t write_idx;
  uint16_t read_idx;
} UsbRingBuf;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define CAN_NEXT_IDX(idx)	(((idx) + 1) % CAN_RINGBUF_SIZE)
#define USB_NEXT_IDX(idx)	(((idx) + 1) % USB_RINGBUF_SIZE)
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern CanRingBuf can_buf;
extern UsbRingBuf usb_buf;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
