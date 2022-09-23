/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum Mode{
	INIT, STATUS, PWM, SPEED, ANGLE, LIM_SW, FIRE, CHASSIS, FIRE_ALL, ANGLE_ALL
}Mode;

typedef enum Chassis{
	FR, FL, BL, BR
}Chassis;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CAN_SIZE 6
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */
void sendPwm(uint32_t address_, bool phase_, int32_t power_);
void moveChassis(int16_t x_, int16_t y_, float yaw_);
void sendFire(uint32_t address_, bool phase_, uint16_t speed_, uint16_t end_);
void sendFireAll(uint32_t address_, bool phase_, uint16_t speed_, uint16_t end_);
void sendAngle(uint32_t address_, bool phase_, uint16_t speed_, uint16_t angle_);
void sendAngleAll(uint32_t address_, bool phase_, uint16_t speed_, uint16_t angle_);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const uint32_t chassis_address[4] = { 0x00, 0x01, 0x02, 0x03 };
const uint32_t fire_address[2] = { 0x04, 0x05 };

uint8_t buffer[6] = {255, 255, 255, 255, 255, 255};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */
  HAL_CAN_Start(&hcan);
  HAL_UART_Receive_IT(&huart2, buffer, 6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 3;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void moveChassis(int16_t x_, int16_t y_, float yaw_){
	int16_t motor_power[4] = {0};

	motor_power[FR] = -sin(M_PI/4)*x_ + cos(M_PI/4)*y_ + yaw_*10;
	motor_power[FL] = -sin(3*M_PI/4)*x_ + cos(3*M_PI/4)*y_ + yaw_*10;
	motor_power[BL] = -sin(5*M_PI/4)*x_ + cos(5*M_PI/4)*y_ + yaw_*10;
	motor_power[BR] = -sin(7*M_PI/4)*x_ + cos(7*M_PI/4)*y_ + yaw_*10;

	for(uint8_t i=0u; i<4;i++){
		sendPwm(chassis_address[i], true, motor_power[i]);
	}
}

void sendPwm(uint32_t address_, bool phase_, int32_t power_){
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t tx_mailbox;
	uint8_t tx_datas[CAN_SIZE];
	uint16_t power = 0;
	bool phase = false;

	if(power_ > 0){
		phase = phase_;
		power = power_;
	}else{
		phase = !phase_;
		power = -power_;
	}

	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) <= 0);

    TxHeader.StdId = address_;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = CAN_SIZE;
    TxHeader.TransmitGlobalTime = DISABLE;
    tx_datas[0] = PWM;
    tx_datas[1] = (uint8_t)phase;
    tx_datas[2] = (power >> 8) & 0xff;
    tx_datas[3] = power & 0xff;
    tx_datas[4] = 0;
    tx_datas[5] = 0;
    HAL_CAN_AddTxMessage(&hcan, &TxHeader, tx_datas, &tx_mailbox);
}

void sendFire(uint32_t address_, bool phase_, uint16_t speed_, uint16_t end_){
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t tx_mailbox;
	uint8_t tx_datas[CAN_SIZE];

	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) <= 0);

	TxHeader.StdId = address_;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = CAN_SIZE;
	TxHeader.TransmitGlobalTime = DISABLE;
	tx_datas[0] = FIRE;
	tx_datas[1] = (uint8_t)phase_;
	tx_datas[2] = (speed_ >> 8) & 0xff;
	tx_datas[3] = speed_ & 0xff;
	tx_datas[4] = (end_ >> 8) & 0xff;
	tx_datas[5] = end_ & 0xff;
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, tx_datas, &tx_mailbox);
}

void sendFireAll(uint32_t address_, bool phase_, uint16_t speed_, uint16_t end_){
	sendFire(address_, phase_, speed_, end_);
	sendFire(address_ + 1, !phase_, speed_, end_);
}

void sendAngle(uint32_t address_, bool phase_, uint16_t speed_, uint16_t angle_){
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t tx_mailbox;
	uint8_t tx_datas[CAN_SIZE];

	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) <= 0);

	TxHeader.StdId = address_;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = CAN_SIZE;
	TxHeader.TransmitGlobalTime = DISABLE;
	tx_datas[0] = ANGLE;
	tx_datas[1] = (uint8_t)phase_;
	tx_datas[2] = (speed_ >> 8) & 0xff;
	tx_datas[3] = speed_ & 0xff;
	tx_datas[4] = (angle_ >> 8) & 0xff;
	tx_datas[5] = angle_ & 0xff;
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, tx_datas, &tx_mailbox);
}

void sendAngleAll(uint32_t address_, bool phase_, uint16_t speed_, uint16_t angle_){
	sendAngle(address_, phase_, speed_, angle_);
	sendAngle(address_ + 1, !phase_, speed_, angle_);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t tx_mailbox;
	uint8_t tx_datas[CAN_SIZE];
	uint32_t address;

	address = ((buffer[0] >> 7) == 1) ? 0x100 : (buffer[0] & 0xff);

	if(((buffer[1] >> 1) & 0x0f) == CHASSIS){
		moveChassis((int16_t)(buffer[0] << 8 | buffer[2]), (int16_t)(buffer[3] << 8 | buffer[4]), (int8_t)buffer[5]);

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

		HAL_UART_Abort(&huart2);
		HAL_UART_Receive_IT(&huart2, buffer, 6);
		return;
	}else if(((buffer[1] >> 1) & 0x0f) == FIRE_ALL){
		sendFireAll(address, (bool)(buffer[1] & 0x01), (uint16_t)(buffer[2] << 8 | buffer[3]), (uint16_t)(buffer[4] << 8 | buffer[5]));

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

		HAL_UART_Abort(&huart2);
		HAL_UART_Receive_IT(&huart2, buffer, 6);
		return;
	}else if(((buffer[1] >> 1) & 0x0f) == ANGLE_ALL){
		sendAngleAll(address, (bool)(buffer[1] & 0x01), (uint16_t)(buffer[2] << 8 | buffer[3]), (uint16_t)(buffer[4] << 8 | buffer[5]));

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

		HAL_UART_Abort(&huart2);
		HAL_UART_Receive_IT(&huart2, buffer, 6);
		return;
	}

//	HAL_UART_Transmit(&huart2, buffer, 6, 100);
	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) <= 0);

	TxHeader.StdId = address;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = CAN_SIZE;
	TxHeader.TransmitGlobalTime = DISABLE;
	tx_datas[0] = (buffer[1] >> 1) & 0x0f;
	tx_datas[1] = (uint8_t)(buffer[1] & 0x01);
	tx_datas[2] = buffer[2];
	tx_datas[3] = buffer[3];
	tx_datas[4] = buffer[4];
	tx_datas[5] = buffer[5];
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, tx_datas, &tx_mailbox);

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

	if(address == 0x100){
		HAL_UART_DeInit(&huart2);
		HAL_UART_Init(&huart2);
	}
	HAL_UART_Abort(&huart2);
	HAL_UART_Receive_IT(&huart2, buffer, 6);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
