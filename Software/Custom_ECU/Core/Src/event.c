/*
 * event.c
 *
 *  Created on: Jun 5, 2022
 *      Author: hugoA
 */

#include "main.h"
#include "event.h"
#include "engine_parameters.h"
#include "ignition.h"
#include "injection.h"

void Cylinder_pin(Cylinder* c)
{
	switch (c->num)
	{
	case(1):
		c->IGN_Pin = (uint16_t) IGN1_Pin;
		c->IGN_GPIO_Port = (GPIO_TypeDef*) IGN1_GPIO_Port;
		c->INJ_Pin = (uint16_t) INJ1_Pin;
		c->INJ_GPIO_Port = (GPIO_TypeDef*) INJ1_GPIO_Port;
		break;

	case(2):
		c->IGN_Pin = (uint16_t) IGN2_Pin;
		c->IGN_GPIO_Port = (GPIO_TypeDef*) IGN2_GPIO_Port;
		c->INJ_Pin = (uint16_t) INJ2_Pin;
		c->INJ_GPIO_Port = (GPIO_TypeDef*) INJ2_GPIO_Port;
		break;

	case(3):
		c->IGN_Pin = (uint16_t) IGN3_Pin;
		c->IGN_GPIO_Port = (GPIO_TypeDef*) IGN3_GPIO_Port;
		c->INJ_Pin = (uint16_t) INJ3_Pin;
		c->INJ_GPIO_Port = (GPIO_TypeDef*) INJ3_GPIO_Port;
		break;

	case(4):
		c->IGN_Pin = (uint16_t) IGN4_Pin;
		c->IGN_GPIO_Port = (GPIO_TypeDef*) IGN4_GPIO_Port;
		c->INJ_Pin = (uint16_t) INJ4_Pin;
		c->INJ_GPIO_Port = (GPIO_TypeDef*) INJ4_GPIO_Port;
		break;
	}
}

void Cylinder_Init(Cylinder list_cylinder[Nb_Cylinder])		// Cyl 1 PMH = 0°
{
	list_cylinder[0].num = 1;
	list_cylinder[0].IGN_PMH = 0;
	Cylinder_pin(&list_cylinder[0]);

	for(int i=1; i<Nb_Cylinder; i++)
	{
		list_cylinder[i].num = i+1;
		list_cylinder[i].IGN_PMH = list_cylinder[i-1].IGN_PMH + Delta_PMH_IGN;
		Cylinder_pin(&list_cylinder[i]);

	}
}

void generate_ignition_event(Cylinder* list_cylinder, float dwell_ms, float speed_rpm, float map,
		float SPEED_IGN[], int SIZE_SPEED_IGN, float MAP_IGN[], int SIZE_MAP_IGN, float* IGN_ADV)
{
	for(int i=0; i<Nb_Cylinder; i++)
	{
		ignition_angle(&list_cylinder[0].charge_angle, &list_cylinder[0].spark_angle, list_cylinder[0].IGN_PMH, dwell_ms, speed_rpm, map, SPEED_IGN, SIZE_SPEED_IGN, MAP_IGN, SIZE_MAP_IGN, IGN_ADV);
	}
}

void generate_injection_event(Cylinder* list_cylinder, float speed_rpm, float map,
		float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ,
		float SPEED_INJ_TIMING[], int SIZE_SPEED_INJ_TIMING, float MAP_INJ_TIMING[], int SIZE_MAP_INJ_TIMING, float* FUEL_INJ_TIMING)
{
	for(int i=0; i<Nb_Cylinder; i++)
	{
		injection_angle(&list_cylinder[0].start_inj_angle, &list_cylinder[0].end_inj_angle, list_cylinder[0].IGN_PMH, speed_rpm, map, SPEED_INJ, SIZE_SPEED_INJ, MAP_INJ, SIZE_MAP_INJ, FUEL_INJ, SPEED_INJ_TIMING,SIZE_SPEED_INJ_TIMING, MAP_INJ_TIMING, SIZE_MAP_INJ_TIMING, FUEL_INJ_TIMING);
	}
}
