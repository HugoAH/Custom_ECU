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
#include "stdbool.h"
#include "engine_parameters.h"
#include "event.h"
#include "ignition.h"
#include "injection.h"
#include "adc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//To discuss if they move to a .h
typedef enum{
	OFF = 0,
	IGNITION_ON = 1,
	CRANKING = 2,
	RUNNING = 3
}engineState_t;

typedef enum{
	SYNCHRO_INIT = 0,
	SYNCHRO_OK = 1,
	SYNCHRO_ERROR = 2
}synchroState_t;

typedef struct EngineStatus{
	engineState_t engineState;
	synchroState_t synchroState;
	bool missmatch_crank_tooth;
	bool missmatch_cam_angle;
}EngineStatus;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
float crank_speed = 0;
float crank_angle = 0;
float delta_integral_crank_angle = 0;
int crank_clock_ovf_counter = 0;
int count_crank_tooth = 0;
bool crank_half_cycle = 0;		// 0: crank_angle=[0,360] ; 1: crank_angle=[360,720]

EngineStatus engine_status = {OFF, SYNCHRO_INIT, false, false};
Cylinder L_Cylinder[NB_CYLINDER] = {0};
Sensor map_sensor = {0};
Sensor mat_sensor = {0};

float speed_rpm = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC1_Init(void);
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  Cylinder_Init(L_Cylinder);
  Sensor_Init(&map_sensor, MAP_Sensor_GPIO_Port, MAP_Sensor_Pin, 1, 0);
  Sensor_Init(&mat_sensor, MAT_Sensor_GPIO_Port, MAT_Sensor_Pin, 1, 0);
  map_sensor.hadc_p = &hadc1;		// Affectation statique à ADC1
  mat_sensor.hadc_p = &hadc1;		// Affectation statique à ADC1
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 840;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, INJ4_Pin|INJ3_Pin|INJ2_Pin|INJ1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, IGN4_Pin|IGN3_Pin|IGN2_Pin|IGN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : INJ4_Pin INJ3_Pin INJ2_Pin INJ1_Pin */
  GPIO_InitStruct.Pin = INJ4_Pin|INJ3_Pin|INJ2_Pin|INJ1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : IGN4_Pin IGN3_Pin IGN2_Pin IGN1_Pin */
  GPIO_InitStruct.Pin = IGN4_Pin|IGN3_Pin|IGN2_Pin|IGN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Hall_cam_Pin */
  GPIO_InitStruct.Pin = Hall_cam_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Hall_cam_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		crank_angle += delta_integral_crank_angle;
		if(engine_status.synchroState == SYNCHRO_OK && engine_status.engineState == RUNNING)
		{
			for(int i=0; i<NB_CYLINDER; i++)
			{
				if(L_Cylinder[i].spark_angle - L_Cylinder[i].charge_angle >= 0)
				{
					L_Cylinder[i].state_pin_ign	= (L_Cylinder[i].charge_angle <= crank_angle) && (crank_angle < L_Cylinder[i].spark_angle);
				}
				else
				{
					L_Cylinder[i].state_pin_ign	= (L_Cylinder[i].charge_angle <= crank_angle) || (crank_angle < L_Cylinder[i].spark_angle);
				}

				if(L_Cylinder[i].end_inj_angle - L_Cylinder[i].start_inj_angle >= 0)
				{
					L_Cylinder[i].state_pin_inj	= (L_Cylinder[i].start_inj_angle <= crank_angle) && (crank_angle < L_Cylinder[i].end_inj_angle);
				}
				else
				{
					L_Cylinder[i].state_pin_inj	= (L_Cylinder[i].start_inj_angle <= crank_angle) || (crank_angle < L_Cylinder[i].end_inj_angle);
				}

				HAL_GPIO_WritePin(L_Cylinder[i].IGN_GPIO_Port, L_Cylinder[i].IGN_Pin, L_Cylinder[i].state_pin_ign);
				HAL_GPIO_WritePin(L_Cylinder[i].INJ_GPIO_Port, L_Cylinder[i].INJ_Pin, L_Cylinder[i].state_pin_inj);
			}
		}
	}

	else if(htim->Instance == TIM1)
	{
		crank_clock_ovf_counter ++;
		if(crank_clock_ovf_counter >= 100)
		{
			delta_integral_crank_angle = 0;
			crank_speed = 0;
			engine_status.engineState = IGNITION_ON;
		}
	}

}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	static bool capture_crank_selector = 0;
	static int capture_value1 = 0;
	static int capture_value2 = 0;
	static float crank_tooth_time = 0;
	static float last_crank_tooth_time = 0;

	if(htim->Instance == TIM1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		int crank_clock_ovf_counter_temp = crank_clock_ovf_counter;
		last_crank_tooth_time = crank_tooth_time;

		if(capture_crank_selector)
		{
			capture_value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			crank_tooth_time = crank_clock_ovf_counter_temp*T_TIMER_CRANK + (capture_value1-capture_value2)*T_CLOCK_CRANK;
		}
		else
		{
			capture_value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			crank_tooth_time = crank_clock_ovf_counter_temp*T_TIMER_CRANK + (capture_value2-capture_value1)*T_CLOCK_CRANK;
		}

		__HAL_TIM_SET_COUNTER(&htim3, 0);
		crank_clock_ovf_counter = 0;

		capture_crank_selector = !capture_crank_selector;
		count_crank_tooth ++;

		if(crank_tooth_time > 1.1*last_crank_tooth_time)		// If we detect a missing tooth event
		{
			engine_status.missmatch_crank_tooth = (count_crank_tooth != CRANK_TOOTH-CRANK_MISSING_TOOTH);

			count_crank_tooth = 0;

			crank_angle = ANGLE_OFFSET + crank_half_cycle*360;
			crank_half_cycle = !crank_half_cycle;

			crank_speed = CRANK_HALL_BTW_TOOTH_ANGLE/(6*crank_tooth_time);	//RPM
			delta_integral_crank_angle = T_ANGLE_UPDATE*CRANK_HALL_BTW_TOOTH_ANGLE/crank_tooth_time;
		}
		else
		{
			engine_status.missmatch_crank_tooth = (count_crank_tooth >= CRANK_TOOTH-CRANK_MISSING_TOOTH);

			crank_angle = CRANK_HALL_BTW_TOOTH_ANGLE*count_crank_tooth + (ANGLE_OFFSET + crank_half_cycle*360);
			crank_speed = CRANK_HALL_BTW_TOOTH_ANGLE/(6*crank_tooth_time);	//RPM
			delta_integral_crank_angle = T_ANGLE_UPDATE*CRANK_HALL_BTW_TOOTH_ANGLE/crank_tooth_time;
		}

		if(engine_status.missmatch_crank_tooth || engine_status.missmatch_cam_angle)
		{
			engine_status.synchroState = SYNCHRO_ERROR;
		}

		read_analog_sensor(&map_sensor);
		read_analog_sensor(&mat_sensor);
		generate_ignition_event(L_Cylinder, dwell_ms, speed_rpm, map_sensor.val, SPEED_IGN, SIZE_SPEED_IGN_TABLE, MAP_IGN, SIZE_MAP_IGN_TABLE, IGN_ADV);
		generate_injection_event(L_Cylinder, speed_rpm, map_sensor.val, SPEED_INJ, SIZE_SPEED_INJ_TABLE, MAP_INJ, SIZE_MAP_INJ_TABLE, FUEL_INJ, SPEED_INJ_TIMING, SIZE_SPEED_INJ_TIMING_TABLE, MAP_INJ_TIMING, SIZE_MAP_INJ_TIMING_TABLE, FUEL_INJ_TIMING);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//Cam sensor implementation
	if (GPIO_Pin == Hall_cam_Pin)
	{
		//Check synchro error if engine is rotating
		if ((crank_angle < SYNC_CRANK_ANGLE_RANGE_MIN || crank_angle > SYNC_CRANK_ANGLE_RANGE_MAX) && engine_status.engineState >= CRANKING)
		{
			switch(engine_status.synchroState)
			{
			case SYNCHRO_INIT:
				crank_half_cycle = !crank_half_cycle;
				break;
			case SYNCHRO_OK:
				engine_status.synchroState = SYNCHRO_ERROR;
				engine_status.missmatch_cam_angle = true;
				Error_Handler(); //Synch_Error_Handler() ?
				break;
			case SYNCHRO_ERROR:
				Error_Handler();
				break;
			}
		}
		//If engine is rotating, the Synchro is OK
		else if (engine_status.engineState >= CRANKING && engine_status.synchroState == SYNCHRO_INIT)
		{
			engine_status.synchroState = SYNCHRO_OK;
		}
	}
}

int __io_putchar(int ch)
{
	uint8_t c;
	c = ch & 0x00FF;
	HAL_UART_Transmit(&huart2, &c, 1, 10);
	return ch;
}
int _write(int file,char *ptr, int len)
{
	int DataIdx;
	for(DataIdx= 0; DataIdx< len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}
	return len;
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
