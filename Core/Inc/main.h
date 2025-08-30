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
#define CAN_TX_SIZE 8
#define CAN_RX_SIZE 8
#define CAN_RINGBUF_SIZE 256

#define USB_RINGBUF_SIZE 64
#define USB_RX_SIZE 8
#define USB_TX_SIZE 8

/* FUNC CODE (4bit) */
#define FUNC_CODE_MASK  (0x0FU << 7)

#define NMT_CODE        (0x00U << 7)
#define SYNC_CODE       (0x01U << 7)
#define EMCY_CODE       (0x02U << 7)
#define TIME_CODE       (0x05U << 7)
#define TX_PDO1_CODE    (0x06U << 7)
#define RX_PDO1_CODE    (0x07U << 7)
#define TX_PDO2_CODE    (0x08U << 7)
#define RX_PDO2_CODE    (0x09U << 7)
#define TX_SDO_CODE     (0x0AU << 7)
#define RX_SDO_CODE     (0x0BU << 7)
#define NMT_ERR_CODE    (0x0CU << 7)

/* TYPE ID (2bit) */
#define TYPE_ID_MASK    (0x03U << 5)

#define MD              (0x01U << 5)
#define OTHER           (0x02U << 5)

/* NODE ID (5bit) */
#define NODE_ID_MASK    0x1FU

/* SPECIAL NODE ID (7bit)*/
#define ALL_NODE_ID_MASK 0x7FU

#define BROADCAST_ID    0x00U
#define USB_CAN_ID      0x01U

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
