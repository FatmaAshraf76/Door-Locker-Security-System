#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* motor HW Ports and Pins Ids */
#define MOTOR_IN1_PORT_ID                 PORTD_ID
#define MOTOR_IN1_PIN_ID                  PIN6_ID

#define MOTOR_IN2_PORT_ID                 PORTD_ID
#define MOTOR_IN2_PIN_ID                  PIN7_ID

#define MOTOR_E_PORT_ID                   PORTB_ID
#define MOTOR_E_PIN_ID                    PIN3_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	CW,A_CW,STOP
}DcMotor_State;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initializes the DC motor by setting the direction for the motor pins and stopping the
 * motor at the beginning.
 */
 void DcMotor_Init(void);

 /*
  * Description :
  * Function responsible for Controls the motor's state (Clockwise/Anti-Clockwise/Stop) and adjusts the speed based
  * on the input duty cycle.
  */
 void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* MOTOR_H_ */
