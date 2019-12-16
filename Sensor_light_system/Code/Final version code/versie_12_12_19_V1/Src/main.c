/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim6;
int status = 0;
// emulated I2C „memory“
static uint8_t ram[11];

uint8_t i = 0;
/*
 * status=0 //bootup
 * status=1 //running main
 * status=2 //running timer callback
 */
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
void updateLED(void){

	switch(status){
	case 0:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0); 				//blauwe led aanzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1); 				//groene led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1); 				//rode led uitzetten
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); 				//blauwe led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0); 				//groene led aanzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1); 				//rode led uitzetten
		break;
	case 2:
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); 				//blauwe led uitzetten
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1); 				//groene led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0); 				//rode led aanzetten
		break;
	/*case running:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false); 				//blauwe led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, true); 				//groene led aanzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, false); 				//rode led uitzetten
		break;*/
	}


}
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
  MX_I2C1_Init();
  MX_TIM6_Init();
  //while(status==0){
	  //updateLED();
	  /* USER CODE BEGIN 2 */
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
	  HAL_TIM_Base_Start_IT(&htim6);
	  HAL_I2C_Init(&hi2c1);
	  status=1;
	  //updateLED();
	  ram[0]= 0xFF;
	  for (int i = 1; i < 11; i++) {
		  ram[i]= i;
	}

  //}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  //updateLED();
	  //HAL_I2C_Slave_Transmit_IT(&hi2c1, (uint8_t *) 20, 1);


	  //HAL_Delay(100);


	  uint32_t I2C_InterruptStatus = I2C1->ISR; /* Get interrupt status */
	  /* Check address match */
	  if ((I2C_InterruptStatus & I2C_ISR_ADDR) == I2C_ISR_ADDR)
	  {
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
	   I2C1->ICR |= I2C_ICR_ADDRCF; /* Clear address match flag */
	   /* Check if transfer direction is read (slave transmitter) */
	   if ((I2C1->ISR & I2C_ISR_DIR) == I2C_ISR_DIR)
	   {
		   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
	   I2C1->CR1 |= I2C_CR1_TXIE; /* Set transmit IT */
	   }
	  }
	  else if ((I2C_InterruptStatus & I2C_ISR_TXIS) == I2C_ISR_TXIS)
	  {
	   I2C1->CR1 &=~ I2C_CR1_TXIE; /* Disable transmit IT */
	   I2C1->TXDR = ram[i]; /* Byte to send */
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
	   if(i<10) {
		   i++;
	   }else i = 0;
	  }
	  HAL_Delay(1);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x0000020B;
  hi2c1.Init.OwnAddress1 = 20;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_ENABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 8000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 100;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	status=2; //running timer callback
	//updateLED();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
	if(htim->Instance==TIM6){

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)==GPIO_PIN_SET){
					  ram[1]= 0xF1;
				  }else{
					  ram[1]= 0x01;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==GPIO_PIN_SET){
					  ram[2]= 0xF2;
				  }else{
					  ram[2]= 0x02;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_SET){
					  ram[3]= 0xF3;
				  }else{
					  ram[3]= 0x03;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_SET){
					  ram[4]= 0xF4;
				  }else{
					  ram[4]= 0x04;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_SET){
					  ram[5]= 0xF5;
				  }else{
					  ram[5]= 0x05;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_SET){
					  ram[6]= 0xF6;
				  }else{
					  ram[6]= 0x06;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==GPIO_PIN_SET){
					  ram[7]= 0xF7;
				  }else{
					  ram[7]= 0x07;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==GPIO_PIN_SET){
					  ram[8]= 0xF8;
				  }else{
					  ram[8]= 0x08;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==GPIO_PIN_SET){
					  ram[9]= 0xF9;
				  }else{
					  ram[9]= 0x09;
				  }
				  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==GPIO_PIN_SET){
					  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
					  ram[10]= 0xFA;
				  }else{
					  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
					  ram[10]= 0x0A;
				  }
	}
	status = 1;
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 PA5 PA6 PA7 
                           PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}











/*void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
  first = 1;
  HAL_I2C_EnableListen_IT(hi2c); // slave is ready again
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{

  if( TransferDirection==I2C_DIRECTION_TRANSMIT ) {
    if( first ) {
      HAL_I2C_Slave_Receive_IT(hi2c, &offset, 1);
    } else {
      HAL_I2C_Slave_Receive_IT(hi2c, &ram[offset], 1);
    }
  } else {
    HAL_I2C_Slave_Transmit_IT(hi2c, &ram[offset], 1);
  }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  if(first) {
    first = 0;
  } else {
    offset++;
  }
  HAL_I2C_Slave_Receive_IT(hi2c, &ram[offset], 1);
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{

  offset++;
  HAL_I2C_Slave_Transmit_IT(hi2c, &ram[offset], 1);
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{

  if( HAL_I2C_GetError(hi2c)==HAL_I2C_ERROR_AF ) {
    offset--; // transaction terminated by master
  } else {
  }
}*/
/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
