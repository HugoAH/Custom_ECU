/*
 * adc.h
 *
 *  Created on: Jun 6, 2022
 *      Author: hugoA
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

typedef struct Sensor{
	GPIO_TypeDef* GPIO_Port;
	uint16_t Sensor_Pin;

	float scaling;
	float offset;

	ADC_HandleTypeDef* hadc_p;
	int adc_channel;

	float val;
}Sensor;

void adc_channel_select(ADC_HandleTypeDef* hadc, int i);
void ADC_pin(Sensor *sensor, GPIO_TypeDef* GPIO_Port, uint16_t Sensor_Pin);
void Sensor_Init(Sensor *sensor, GPIO_TypeDef* GPIO_Port, uint16_t Sensor_Pin, float scaling, float offset);
void read_analog_sensor(Sensor *sensor);

#endif /* INC_ADC_H_ */
