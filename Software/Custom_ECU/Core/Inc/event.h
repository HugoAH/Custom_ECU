/*
 * event.h
 *
 *  Created on: Jun 5, 2022
 *      Author: hugoA
 */

#ifndef INC_EVENT_H_
#define INC_EVENT_H_

void generate_PMH_IGN(float* l);
void generate_ignition_event(float* list_ignition_event, float* list_pmh, float dwell_ms, float speed_rpm, float MAP, float SPEED_IGN[], int SIZE_SPEED_IGN, float MAP_IGN[], int SIZE_MAP_IGN, float* IGN_ADV);
void generate_injection_event(float* list_injection_event, float* list_pmh, float speed_rpm, float map,
		float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ,
		float SPEED_INJ_TIMING[], int SIZE_SPEED_INJ_TIMING, float MAP_INJ_TIMING[], int SIZE_MAP_INJ_TIMING, float* FUEL_INJ_TIMING);
#endif /* INC_EVENT_H_ */
