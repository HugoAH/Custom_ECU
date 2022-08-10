/*
 * event.h
 *
 *  Created on: Jun 5, 2022
 *      Author: hugoA
 */

#ifndef INC_EVENT_H_
#define INC_EVENT_H_

typedef struct Cylinder{
	int num;
	GPIO_TypeDef* IGN_GPIO_Port;
	uint16_t IGN_Pin;
	GPIO_TypeDef* INJ_GPIO_Port;
	uint16_t INJ_Pin;

	float IGN_PMH;

	float charge_angle;
	float spark_angle;

	float start_inj_angle;
	float end_inj_angle;

	bool state_pin_ign;
	bool state_pin_inj;

	float lbda;
}Cylinder;

void Cylinder_pin(Cylinder* c);
void Cylinder_Init(Cylinder* l);
void generate_ignition_event(Cylinder* l, float dwell_ms, float speed_rpm, float MAP, float SPEED_IGN[], int SIZE_SPEED_IGN, float MAP_IGN[], int SIZE_MAP_IGN, float* IGN_ADV);
void generate_injection_event(Cylinder* l, float speed_rpm, float map,
		float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ,
		float SPEED_INJ_TIMING[], int SIZE_SPEED_INJ_TIMING, float MAP_INJ_TIMING[], int SIZE_MAP_INJ_TIMING, float* FUEL_INJ_TIMING);

#endif /* INC_EVENT_H_ */
