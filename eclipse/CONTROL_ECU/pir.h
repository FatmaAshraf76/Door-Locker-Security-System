#ifndef PIR_H_
#define PIR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PEOPLE_ENTER                       0x01
#define NO_ONE_ENTER                       0x00

#define PIR_SENSOR_PORT_ID                 PORTC_ID
#define PIR_SENSOR_PIN_ID                  PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 *  Function to initialize the PIR driver
 *  Inputs: None
 *  Return: None
 */
void PIR_init(void);

/*
 * Description :
 *  Function Function to return PIR State
 *  Inputs: None
 *  Return: uint8
 */
uint8 PIR_getState(void);

#endif /* PIR_H_ */
