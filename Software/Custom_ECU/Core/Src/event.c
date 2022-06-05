/*
 * event.c
 *
 *  Created on: Jun 5, 2022
 *      Author: hugoA
 */

#include "event.h"
#include "engine_parameters.h"
#include "ignition.h"
#include "injection.h"

void generate_PMH_IGN(float* l)		// Cyl 1 PMH = 0°
{
	l[0] = 0;
	for(int i=1; i<Nb_Cylinder; i++)
	{
		l[i] = l[i-1] + Delta_PMH_IGN;
	}
}

void generate_ignition_event(float* list_ignition_event, float* list_pmh, float dwell_ms, float speed_rpm, float map,
		float SPEED_IGN[], int SIZE_SPEED_IGN, float MAP_IGN[], int SIZE_MAP_IGN, float* IGN_ADV)
{
	// list_ignition_event[Nb_Cylinder][2] : angle charge, angle spark
	for(int i=0; i<Nb_Cylinder; i++)
	{
		ignition_angle(&list_ignition_event[2*i], &list_ignition_event[2*i+1], list_pmh[i], dwell_ms, speed_rpm, map, SPEED_IGN, SIZE_SPEED_IGN, MAP_IGN, SIZE_MAP_IGN, IGN_ADV);
	}
}

void generate_injection_event(float* list_injection_event, float* list_pmh, float speed_rpm, float map,
		float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ,
		float SPEED_INJ_TIMING[], int SIZE_SPEED_INJ_TIMING, float MAP_INJ_TIMING[], int SIZE_MAP_INJ_TIMING, float* FUEL_INJ_TIMING)
{
	// list_injection_event[Nb_Cylinder][2] : angle charge, angle spark
	for(int i=0; i<Nb_Cylinder; i++)
	{
		injection_angle(&list_injection_event[2*i], &list_injection_event[2*i+1], list_pmh[i], speed_rpm, map, SPEED_INJ, SIZE_SPEED_INJ, MAP_INJ, SIZE_MAP_INJ, FUEL_INJ, SPEED_INJ_TIMING,SIZE_SPEED_INJ_TIMING, MAP_INJ_TIMING, SIZE_MAP_INJ_TIMING, FUEL_INJ_TIMING);
	}
}
