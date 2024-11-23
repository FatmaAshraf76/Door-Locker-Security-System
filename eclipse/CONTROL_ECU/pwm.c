#include "common_macros.h" /* For GET_BIT Macro */
#include "pwm.h"
#include "gpio.h"
#include "avr/io.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*
 * Description:
 * Initializes Timer0 in PWM mode and sets the required duty cycle.
 * Prescaler: F_CPU/64
 *  Non-inverting mode
 *  The function configures OC0 as the output pin.
 */

void PWM_Timer0_Start(void)
{
	TCNT0 = 0; // Set Timer Initial Value to 0

	// Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC
	GPIO_setupPinDirection(PWM_E_PORT_ID, PWM_E_PIN_ID ,PIN_OUTPUT);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/64 CS00=1 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00) | (1<<CS01);

}

void duty_cycle(uint8 duty_cycle)
{
	OCR0  = (uint8)(((uint32)duty_cycle*PWM_MAX_OUTPUT)/(MOTOR_MAX_SPEED)); // Set Compare Value
}

