/*
 * engine_wheel_parameters.h
 *
 *  Created on: May 28, 2022
 *      Author: hugoA
 */

#ifndef INC_ENGINE_PARAMETERS_H_
#define INC_ENGINE_PARAMETERS_H_


#define Nb_Cylinder 3
#define Delta_PMH_IGN 720/Nb_Cylinder

/***************** CRANKSHAFT PARAMETERS  ******************************/
#define CRANK_TOOTH 26
#define CRANK_MISSING_TOOTH 2
#define CRANK_HALL_ANGLE 360/(CRANK_TOOTH-CRANK_MISSING_TOOTH)
#define CRANK_HALL_MISS_ANGLE (1+CRANK_MISSING_TOOTH)*CRANK_HALL_ANGLE

#define T_CLOCK_TIM4 1/(64e6)
#define T_TIM4 T_CLOCK_TIM4*65535

#define T_ANGLE_UPDATE 1e-6
#define ANGLE_OFFSET 0			//crank angle at the 1st tooth after missing gap (0° = IGN PMH Cylinder1)

/***************** CAMSHAFT PARAMETERS  ******************************/
/*Minimum and maximum expected values of the crankshaft angle
when the camshaft is detected*/
#define SYNC_CRANK_ANGLE_RANGE_MIN 120
#define SYNC_CRANK_ANGLE_RANGE_MAX 360




#endif /* INC_ENGINE_PARAMETERS_H_ */
