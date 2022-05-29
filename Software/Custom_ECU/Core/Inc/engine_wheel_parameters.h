/*
 * engine_wheel_parameters.h
 *
 *  Created on: May 28, 2022
 *      Author: hugoA
 */

#ifndef INC_ENGINE_WHEEL_PARAMETERS_H_
#define INC_ENGINE_WHEEL_PARAMETERS_H_

#define CRANK_TOOTH 26
#define CRANK_MISSING_TOOTH 2
#define CRANK_HALL_ANGLE 360/(CRANK_TOOTH-CRANK_MISSING_TOOTH)

#define T_CLOCK_TIM4 1/(64e6)
#define T_TIM4 T_CLOCK_TIM4*65535

#endif /* INC_ENGINE_WHEEL_PARAMETERS_H_ */
