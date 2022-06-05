/*
 * ignition.h
 *
 *  Created on: 3 juin 2022
 *      Author: hugoA
 */

#ifndef INC_IGNITION_H_
#define INC_IGNITION_H_

#define SIZE_SPEED_IGN_TABLE 10
#define SIZE_MAP_IGN_TABLE 10

extern float SPEED_IGN[SIZE_SPEED_IGN_TABLE];
extern float MAP_IGN[SIZE_MAP_IGN_TABLE];
extern float* IGN_ADV;

extern float dwell_ms;

float dwell_to_angle(float dwell_time, float speed);
void ignition_angle(float* charge_angle, float* adv_angle, float PMH_angle, float dwell_ms, float speed_rpm, float map, float SPEED_IGN[], int SIZE_SPEED_IGN, float MAP_IGN[], int SIZE_MAP_IGN, float* IGN_ADV);



#endif /* INC_IGNITION_H_*/
