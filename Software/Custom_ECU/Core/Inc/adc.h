/*
 * adc.h
 *
 *  Created on: Jun 6, 2022
 *      Author: hugoA
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

typedef struct Sensor{
	ADC_HandleTypeDef* hadc_p;
	int adc_channel;

	float scaling;
	float offset;
	float val;
}Sensor;

void adc_channel_select(ADC_HandleTypeDef* hadc, int i);
void Sensor_Init(Sensor *sensor);

#endif /* INC_ADC_H_ */
