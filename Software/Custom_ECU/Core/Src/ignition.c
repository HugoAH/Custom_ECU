/*
 * ignition.c
 *
 *  Created on: 3 juin 2022
 *      Author: hugoA
 */

#include "ignition.h"
#include "interpolation.h"

float dwell_to_angle(float dwell_ms, float speed_rpm)
{
	float dwell_angle = dwell_ms*speed_rpm*6/1000.0;
	return(dwell_angle);
}

void ignition_angle(float* charge_angle, float* spark_angle, float PMH_angle, float dwell_ms, float speed_rpm, float MAP, float SPEED_IGN[], int SIZE_SPEED_IGN, float MAP_IGN[], int SIZE_MAP_IGN, float* IGN_ADV)
{
	float adv_angle = lookup_table2D_interpolation(speed_rpm, MAP, SPEED_IGN, SIZE_SPEED_IGN, MAP_IGN, SIZE_MAP_IGN, IGN_ADV);
	float dwell_angle = dwell_to_angle(dwell_ms, speed_rpm);

	*spark_angle = PMH_angle - adv_angle;		//Angle to stop current in primary circuit of sparkplug transformer
	*charge_angle = *spark_angle - dwell_angle;	//Angle to begin the charge of primary circuit of sparkplug transformer
}
