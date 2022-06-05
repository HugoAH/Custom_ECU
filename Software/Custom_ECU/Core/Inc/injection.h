/*
 * injection.h
 *
 *  Created on: Jun 3, 2022
 *      Author: hugoA
 */

#ifndef INC_INJECTION_H_
#define INC_INJECTION_H_

#define TIME_INJ_OPENNING 1
#define Q_INJ 1


#define SIZE_SPEED_INJ_TABLE 10
#define SIZE_MAP_INJ_TABLE 10

#define SIZE_SPEED_INJ_TIMING_TABLE 10
#define SIZE_MAP_INJ_TIMING_TABLE 10


extern float SPEED_INJ[SIZE_SPEED_INJ_TABLE];
extern float MAP_INJ[SIZE_MAP_INJ_TABLE];
extern float* FUEL_INJ;

extern float SPEED_INJ_TIMING[SIZE_SPEED_INJ_TIMING_TABLE];
extern float MAP_INJ_TIMING[SIZE_MAP_INJ_TIMING_TABLE];
extern float* FUEL_INJ_TIMING;



float time_to_angle(float time_ms, float speed_rpm);
float fuel_to_time(float fuel_qte, float flow_rate);
float fuel_eq(float pressure, float VE, float temperature, float lbda_target);

float mass_fuel_to_inject(float speed_rpm, float map,float temperature, float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ);

void VE_injection_angle(float* start_inj_angle, float* end_inj_angle, float PMH_angle, float speed_rpm, float map, float temperature, float flow_rate,
float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ,
float SPEED_INJ_TIMING[], int SIZE_SPEED_INJ_TIMING, float MAP_INJ_TIMING[], int SIZE_MAP_INJ_TIMING, float* FUEL_INJ_TIMING);

void injection_angle(float* start_inj_angle, float* end_inj_angle, float PMH_angle, float speed_rpm, float map,
float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ,
float SPEED_INJ_TIMING[], int SIZE_SPEED_INJ_TIMING, float MAP_INJ_TIMING[], int SIZE_MAP_INJ_TIMING, float* FUEL_INJ_TIMING);

#endif /* INC_INJECTION_H_ */
