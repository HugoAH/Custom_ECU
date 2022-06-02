/*
 * ignition.h
 *
 *  Created on: 3 juin 2022
 *      Author: hugoA
 */

#ifndef INC_IGNITION_H_
#define INC_IGNITION_H_

float dwell_to_angle(float dwell_time, float speed);
void ignition_angle(float* charge_angle, float* adv_angle, float PMH_angle, float dwell_ms, float speed_rpm, float MAP, float SPEED_IGN[], int SIZE_SPEED_IGN, float MAP_IGN[], int SIZE_MAP_IGN, float* IGN_ADV);


#endif /* INC_IGNITION_H_ */
