#include "common_macros.h" /* For GET_BIT Macro */
#include "timer.h"
#include "gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/********************************************************/
/*                 Global variables                     */
/********************************************************/
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_Timer0CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer1CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer2CallBackPtr)(void) = NULL_PTR;


/********************************************************/
/*                   ISR functions                      */
/********************************************************/

ISR(TIMER0_OVF_vect) {
	if (g_Timer0CallBackPtr != NULL_PTR)
	{
		(*g_Timer0CallBackPtr)();
	}
}
ISR(TIMER0_COMP_vect) {
	if (g_Timer0CallBackPtr != NULL_PTR)
	{
		(*g_Timer0CallBackPtr)();
	}
}

ISR(TIMER1_OVF_vect) {
	if (g_Timer1CallBackPtr != NULL_PTR)
	{
		(*g_Timer1CallBackPtr)();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if (g_Timer1CallBackPtr != NULL_PTR) {
		(*g_Timer1CallBackPtr)();
	}
}

ISR(TIMER2_OVF_vect)
{
	if (g_Timer2CallBackPtr != NULL_PTR) {
		(*g_Timer2CallBackPtr)();
	}
}
ISR(TIMER2_COMP_vect)
{
	if (g_Timer2CallBackPtr != NULL_PTR) {
		(*g_Timer2CallBackPtr)();
	}
}

/*******************************************************************************/
/*                      Functions Definitions                                  */
/*******************************************************************************/

/*
 * Description:
 *  Function to initialize the Timer driver
 *  Inputs: pointer to the configuration structure with type Timer_ConfigType.
 *  Return: None
 */
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	if (Config_Ptr->timer_ID == TIMER0)
	{
		SET_BIT(TCCR0,FOC0);
		TCNT0 = Config_Ptr->timer_InitialValue;
		TCCR0 = 0;
		TCCR0 |= (Config_Ptr->timer_clock);
		if (Config_Ptr->timer_mode == Normal_Mode)
		{
			SET_BIT(TIMSK,TOIE0);
			SET_BIT(TIFR,TOV0);
		}
		else if (Config_Ptr->timer_mode == CTC_Mode)
		{
			SET_BIT(TCCR0,WGM01);
			OCR0 = Config_Ptr->timer_compare_MatchValue;
			SET_BIT(TIMSK,OCIE0);
			SET_BIT(TIFR,OCF0);
		}
	}
	else if (Config_Ptr->timer_ID == TIMER1)
	{
		TCCR1A =0;
		SET_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1A,FOC1B);
		TCCR1B = Config_Ptr->timer_clock;
		TCNT1 = Config_Ptr->timer_InitialValue;
		if (Config_Ptr->timer_mode == Normal_Mode)
		{
			SET_BIT(TIMSK, TOIE1);
			SET_BIT(TIFR,TOV1);
		}
		else if (Config_Ptr->timer_mode == CTC_Mode)
		{
			SET_BIT(TCCR1B, WGM12);
			OCR1A = Config_Ptr->timer_compare_MatchValue;
			SET_BIT(TIMSK, OCIE1A);
			SET_BIT(TIFR,OCF1A);
		}
	}
	else if (Config_Ptr->timer_ID == TIMER2)
	{
		SET_BIT(TCCR2, FOC2);
		TCNT2 = Config_Ptr->timer_InitialValue;
		TCCR2 = 0;
		TCCR2 |= (Config_Ptr->timer_clock);
		if (Config_Ptr->timer_mode == Normal_Mode)
		{
			SET_BIT(TIMSK, TOIE2);
			SET_BIT(TIFR,TOV2);
		}
		else if (Config_Ptr->timer_mode == CTC_Mode)
		{
			SET_BIT(TCCR0, WGM21);
			OCR2 = Config_Ptr->timer_compare_MatchValue;
			SET_BIT(TIMSK, OCIE2);
			SET_BIT(TIFR,OCF2);
		}
	}
}

/*
 * Description:
 *   Function to disable the Timer via Timer_ID.
 *   Inputs: Timer_ID
 *   Return: None
 */
void Timer_deInit(Timer_ID_Type timer_type)
{
	if (timer_type==TIMER0)
	{
		OCR0=0;
		TCCR0=0;
		TCNT0= 0;
		CLEAR_BIT(TIMSK,OCIE0);
		CLEAR_BIT(TIMSK,TOIE0);
		g_Timer0CallBackPtr=NULL_PTR;
	}
	else if (timer_type==TIMER1)
	{
		OCR1A=0;
		TCCR1A=0;
		TCCR1B=0;
		TCNT1=0;
		CLEAR_BIT(TIMSK,TOIE1);
		CLEAR_BIT(TIMSK,OCIE1A);
		g_Timer1CallBackPtr=NULL_PTR;
	}
	else if (timer_type==TIMER2)
	{
		OCR2=0;
		TCCR2=0;
		TCNT2=0;
		CLEAR_BIT(TIMSK,OCIE2);
		CLEAR_BIT(TIMSK,TOIE2);
		g_Timer2CallBackPtr=NULL_PTR;
	}
}

/*
 * Description:
 *   Function to set the Call Back function address to the required Timer.
 *   Inputs: pointer to Call Back function and Timer Id you want to set The Callback to it.
 *   Return: None
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID )
{
	if(a_timer_ID==TIMER0)
	{
		g_Timer0CallBackPtr=a_ptr;
	}
	else if(a_timer_ID==TIMER1)
	{
		g_Timer1CallBackPtr=a_ptr;
	}
	else if(a_timer_ID==TIMER2)
	{
		g_Timer2CallBackPtr=a_ptr;
	}
}
