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
#include "stm32f0xx_hal.h"
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
  typedef enum status{
	  init = 0,
	  sending = 1,
	  sended = 2,
	  running = 3
  };

  bool data_old[10]={0,0,0,0,0,0,0,0,0,0};
  bool data_new[10]={0,0,0,0,0,0,0,0,0,0};
  bool flags[10]={0,0,0,0,0,0,0,0,0,0};
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
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM6_Init();
  HAL_TIM_Base_Init(htim6);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */


  //HAL_TIM_PeriodElapsedCallback(htim6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  status=init;
	  while(status==init){
		  updateLED();
		  if(HAL_I2C_IsDeviceReady(&hi2c1, 0xFF, 10, 100)==HAL_OK){
			  HAL_TIM_Base_Start(htim6);
			  status=running;
		  }

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false); 				//blauwe led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, false); 				//groene led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, false); 				//rode led uitzetten
		HAL_Delay(100);
	  }



	HAL_Delay(1000);
	status=running;
	updateLED();

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void updateLED(void){

	switch(status){
	case init:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, true); 				//blauwe led aanzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, false); 				//groene led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, false); 				//rode led uitzetten
		break;
	case sending:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false); 				//blauwe led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, false); 				//groene led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, true); 				//rode led aanzetten
		break;
	case sended:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false); 				//blauwe led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, true); 				//groene led aanzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, true); 				//rode led aanzetten
		break;
	case running:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false); 				//blauwe led uitzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, true); 				//groene led aanzetten
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, false); 				//rode led uitzetten
		break;
	}


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
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0x01;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
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
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */
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
  htim6.Init.Prescaler = 800;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance==TIM6){
		status=sending;
		updateLED();
		for(int i = 0; i<9; i++){
			data_old[i]=data_new[i];
			data_new[i]=0;

			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_i)==GPIO_PIN_SET){
				//sensor detect
				data_new[i]=1;
			}
			if(data_old[i] == data_new[i]){
				flags[i]= 0;
			}else{
				if(data_new[j]){
					HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) j+1, 1 , 100);
				}else HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) j+241, 1 , 100);
				flags[i]= 1;
			}
		}
		status=sended;
		updateLED();

		/*for(uint_8t j = 0; j<9; j++){
			if(flags[j]){
				if(data_new[j]){
					HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) j+1, 1 , 100);
				}else HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) j+241, 1 , 100);
			}
		}*/

		/*if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)==GPIO_PIN_SET){
				//sensor1 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x01, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==GPIO_PIN_SET){
				//sensor2 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x02, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_SET){
				//sensor3 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x03, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_SET){
				//sensor4 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x04, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_SET){
				//sensor5 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x05, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_SET){
				//sensor6 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x06, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==GPIO_PIN_SET){
				//sensor7 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x07, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==GPIO_PIN_SET){
				//sensor8 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x08, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==GPIO_PIN_SET){
				//sensor9 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x09, 1 , 100);
			}
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==GPIO_PIN_SET){
				//sensor10 detect
				HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t *) 0x0A, 1 , 100);
			}*/
	}
}
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
