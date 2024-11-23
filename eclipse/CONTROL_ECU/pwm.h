/*
 * pwm.h
 *
 *  Created on: Oct 4, 2024
 *      Author: lenovo
 */

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PWM_E_PORT_ID                  PORTB_ID
#define PWM_E_PIN_ID                   PIN3_ID

#define MOTOR_MAX_SPEED                  100
#define PWM_MAX_OUTPUT                   255

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for control the fan's speed based on the temperature.
 *  The driver uses Timer0 in PWM mode.
 */
void PWM_Timer0_Start(void);
void duty_cycle(uint8 duty_cycle);


#endif /* PWM_H_ */
