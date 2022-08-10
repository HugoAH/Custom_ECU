/*
 * engine_wheel_parameters.h
 *
 *  Created on: May 28, 2022
 *      Author: hugoA
 */

#ifndef INC_ENGINE_PARAMETERS_H_
#define INC_ENGINE_PARAMETERS_H_


#define NB_CYLINDER 3
#define ANGLE_BTW_PMH 720/NB_CYLINDER

/***************** CRANKSHAFT PARAMETERS  ******************************/
#define CRANK_TOOTH 26
#define CRANK_MISSING_TOOTH 2
#define CRANK_HALL_BTW_TOOTH_ANGLE 360/(CRANK_TOOTH-CRANK_MISSING_TOOTH)
#define CRANK_HALL_MISSING_TOOTH_ANGLE (1+CRANK_MISSING_TOOTH)*CRANK_HALL_ANGLE

#define T_CLOCK_CRANK 1/(84e6)
#define T_TIMER_CRANK T_CLOCK_CRANK*65535

#define T_ANGLE_UPDATE 10e-6	// Time cst for crank angle integration
#define ANGLE_OFFSET 0			// Crank angle between TDC of cylinder 1 and 1st tooth after missing tooth

/***************** CAMSHAFT PARAMETERS  ******************************/
/*Minimum and maximum expected values of the crankshaft angle
when the camshaft is detected*/
#define SYNC_CRANK_ANGLE_RANGE_MIN 120
#define SYNC_CRANK_ANGLE_RANGE_MAX SYNC_CRANK_ANGLE_RANGE_MIN + 180




#endif /* INC_ENGINE_PARAMETERS_H_ */
