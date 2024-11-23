#include "common_macros.h" /* For GET_BIT Macro */
#include "gpio.h"
#include "pir.h"


uint8 prev_pir_value = 0;
uint8 flag = 0;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 *  Function to initialize the PIR driver
 *  Inputs: None
 *  Return: None
 */
void PIR_init(void)
{
	GPIO_setupPinDirection(PIR_SENSOR_PORT_ID, PIR_SENSOR_PIN_ID , PIN_INPUT);
}

/*
 * Description :
 *  Function to return PIR State
 *  Inputs: None
 *  Return: uint8
 */
uint8 PIR_getState(void)
{
	uint8 state;
	state=GPIO_readPin(PIR_SENSOR_PORT_ID, PIR_SENSOR_PIN_ID);
	if(state==LOGIC_HIGH)
	{
		return PEOPLE_ENTER;
	}
	else
	{
        return NO_ONE_ENTER;
	}

}


