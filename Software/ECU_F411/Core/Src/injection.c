/*
 * injection.c
 *
 *  Created on: Jun 3, 2022
 *      Author: hugoA
 */

#include <math.h>
#include "injection.h"
#include "interpolation.h"

// lookup table qte fuel
float SPEED_INJ[SIZE_SPEED_INJ_TABLE] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
float MAP_INJ[SIZE_MAP_INJ_TABLE] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
float* FUEL_INJ;

// lookup table start injecting
float SPEED_INJ_TIMING[SIZE_SPEED_INJ_TIMING_TABLE] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
float MAP_INJ_TIMING[SIZE_MAP_INJ_TIMING_TABLE] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
float* FUEL_INJ_TIMING;



float time_to_angle(float time_ms, float speed_rpm)
{
	float angle = time_ms*speed_rpm*6/1000.0;
	return(angle);
}

float fuel_to_time(float fuel_qte, float flow_rate)
{
  return(fuel_qte/flow_rate);
}

/*
float mass_fuel_eq(float pressure, float VE, float temperature, float lbda_target)
{
  // https://adaptronicecu.com/blogs/modular-instructional-videos/fuel-model-in-modular-ecus

  const int Wair = 29;    // g/mol
  const float R = 8.314;  // J/K/mol
  float AFR_stoech = 14.1;
  float Vcyl = 10e-6;
  float mass_fuel = pressure*VE*Vcyl/(R/Wair*temperature*lbda_target*AFR_stoech);

  return(mass_fuel);
}

float fuel_to_inject(float speed_rpm, float map, float temperature, float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ)
{
  float lbda_target = 1;
  float VE = lookup_table2D_interpolation(speed_rpm, map, SPEED_INJ, SIZE_SPEED_INJ, MAP_INJ, SIZE_MAP_INJ, FUEL_INJ);
  float fuel_qte = mass_fuel_eq(map, VE, temperature, lbda_target);
  return(fuel_qte);
}

// VE TABLE
void VE_injection_angle(float* start_inj_angle, float* end_inj_angle, float PMH_angle, float speed_rpm, float map, float temperature, float flow_rate,
float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ,
float SPEED_INJ_TIMING[], int SIZE_SPEED_INJ_TIMING, float MAP_INJ_TIMING[], int SIZE_MAP_INJ_TIMING, float* FUEL_INJ_TIMING)
{
  *start_inj_angle = fmod(PMH_angle - lookup_table2D_interpolation(speed_rpm, map, SPEED_INJ_TIMING, SIZE_SPEED_INJ_TIMING, MAP_INJ_TIMING, SIZE_MAP_INJ_TIMING, FUEL_INJ_TIMING), 720);

  float fuel_qte = fuel_to_inject(speed_rpm, map, temperature, SPEED_INJ, SIZE_SPEED_INJ, MAP_INJ, SIZE_MAP_INJ, FUEL_INJ);
  float fuel_time = fuel_to_time(fuel_qte, flow_rate);
  float fuel_angle = time_to_angle(fuel_time, speed_rpm);

  *end_inj_angle = fmod((*start_inj_angle + fuel_angle), 720);
  *start_inj_angle = fmod(*start_inj_angle - time_to_angle(TIME_INJ_OPENNING, speed_rpm), 720);
}
*/

// INJECTION DURATION TABLE
void injection_angle(float* start_inj_angle, float* end_inj_angle, float PMH_angle, float speed_rpm, float map,
float SPEED_INJ[], int SIZE_SPEED_INJ, float MAP_INJ[], int SIZE_MAP_INJ, float* FUEL_INJ,
float SPEED_INJ_TIMING[], int SIZE_SPEED_INJ_TIMING, float MAP_INJ_TIMING[], int SIZE_MAP_INJ_TIMING, float* FUEL_INJ_TIMING)
{
	*start_inj_angle = fmod(PMH_angle - lookup_table2D_interpolation(speed_rpm, map, SPEED_INJ_TIMING, SIZE_SPEED_INJ_TIMING, MAP_INJ_TIMING, SIZE_MAP_INJ_TIMING, FUEL_INJ_TIMING), 720);

	float fuel_time = lookup_table2D_interpolation(speed_rpm, map, SPEED_INJ, SIZE_SPEED_INJ, MAP_INJ, SIZE_MAP_INJ, FUEL_INJ);
	float fuel_angle = time_to_angle(fuel_time, speed_rpm);

	*end_inj_angle = fmod((*start_inj_angle + fuel_angle), 720);
	*start_inj_angle = fmod(*start_inj_angle - time_to_angle(MS_INJ_OPENNING, speed_rpm), 720);
}
