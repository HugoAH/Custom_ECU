/*
 * adc.c
 *
 *  Created on: Jun 6, 2022
 *      Author: hugoA
 */

#include "main.h"
#include "adc.h"

void adc_channel_select(ADC_HandleTypeDef* hadc, int i)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	switch (i)
	{
	case 0:
			sConfig.Channel = ADC_CHANNEL_0;
			break;
	case 1:
			sConfig.Channel = ADC_CHANNEL_1;
			break;
	case 2:
			sConfig.Channel = ADC_CHANNEL_2;
			break;
	case 3:
			sConfig.Channel = ADC_CHANNEL_3;
			break;
	case 4:
			sConfig.Channel = ADC_CHANNEL_4;
			break;
	case 5:
			sConfig.Channel = ADC_CHANNEL_5;
			break;
	case 6:
			sConfig.Channel = ADC_CHANNEL_6;
			break;
	case 7:
			sConfig.Channel = ADC_CHANNEL_7;
			break;
	case 8:
			sConfig.Channel = ADC_CHANNEL_8;
			break;
	case 9:
			sConfig.Channel = ADC_CHANNEL_9;
			break;
	case 10:
			sConfig.Channel = ADC_CHANNEL_10;
			break;
	case 11:
			sConfig.Channel = ADC_CHANNEL_11;
			break;
	case 12:
			sConfig.Channel = ADC_CHANNEL_12;
			break;
	case 13:
			sConfig.Channel = ADC_CHANNEL_13;
			break;
	case 14:
			sConfig.Channel = ADC_CHANNEL_14;
			break;
	case 15:
			sConfig.Channel = ADC_CHANNEL_15;
			break;
	}
	sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
	if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
	{
	Error_Handler();
	}
}

void Sensor_Init(Sensor *sensor)	//associate to the sensor to the correct adc & channel
{
	//sensor->hadc_p = &hadc??;
	//sensor->adc_channel = ??;
}

void read_analog_sensor(Sensor *sensor)
{
	adc_channel_select(sensor->hadc_p, sensor->adc_channel);
	HAL_ADC_Start(sensor->hadc_p);
    HAL_ADC_PollForConversion(sensor->hadc_p, 1);
    int raw_bits = HAL_ADC_GetValue(sensor->hadc_p);
    float raw_voltage = (float) raw_bits*3.3/4095;		// to check
	sensor->val = sensor->scaling * raw_voltage + sensor->offset;
}
