/*
 * ignition.c
 *
 *  Created on: 3 juin 2022
 *      Author: hugoA
 */

#include <math.h>
#include "ignition.h"
#include "interpolation.h"

// lookup table ignition advance
float SPEED_IGN[SIZE_SPEED_IGN_TABLE] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
float MAP_IGN[SIZE_MAP_IGN_TABLE] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
float* IGN_ADV;	//ignition advance table

float dwell_ms = 1;


float dwell_to_angle(float dwell_ms, float speed_rpm)
{
	float dwell_angle = dwell_ms*speed_rpm*6/1000.0;
	return(dwell_angle);
}

void ignition_angle(float* charge_angle, float* spark_angle, float PMH_angle, float dwell_ms, float speed_rpm, float map, float SPEED_IGN[], int SIZE_SPEED_IGN, float MAP_IGN[], int SIZE_MAP_IGN, float* IGN_ADV)
{
	float adv_angle = lookup_table2D_interpolation(speed_rpm, map, SPEED_IGN, SIZE_SPEED_IGN, MAP_IGN, SIZE_MAP_IGN, IGN_ADV);
	float dwell_angle = dwell_to_angle(dwell_ms, speed_rpm);

	*spark_angle = fmod(PMH_angle - adv_angle, 720);		//Angle to stop current in primary circuit of sparkplug transformer
	*charge_angle = fmod(*spark_angle - dwell_angle, 720);	//Angle to begin the charge of primary circuit of sparkplug transformer
}
