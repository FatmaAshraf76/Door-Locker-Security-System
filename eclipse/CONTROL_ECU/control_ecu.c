#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "motor.h"
#include "timer.h"
#include "buzzer.h"
#include "pwm.h"
#include "twi.h"
#include "pir.h"
#include "external_eeprom.h"
#include "gpio.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PASSWORD_ADDRESS        0x0311

#define PASSWORD_MAX_SIZE      5
#define PASSWORD_MAX_trial     2
#define MATCHED                1
#define UNMATCHED              0

#define READY                  0x10
#define EEPROM_SAVE_PASSWORD   0x11
#define ENTER_PASSWORD         0x12
#define Chanage_PASSWORD       0x13
#define DOOR_OPEN              0x14
#define DOOR_CLOSE             0X15
#define DOOR_STOP              0x16
#define BUZZER_ON              0x17
#define BUZZER_OFF             0x18
#define ENTER                  0x0D


uint8 password1[PASSWORD_MAX_SIZE];
uint8 password2[PASSWORD_MAX_SIZE];

/* global variable contain the ticks count of the timer */
uint32 seconds = 0;
uint8 try_agin=0;


/*******************************************************************************/
/*                      Functions Prototypes                                   */
/*******************************************************************************/
void Timer_CallBack(void);
void Recive_password(void);
uint8 compare_password(void);
void EEPROM_save_pass(void);
void open_Door(void);


/*******************************************************************************/
/*                      main application                                       */
/*******************************************************************************/

int main(void)
{
	/* Initialize the TIMER driver */
	Timer_ConfigType TIMER_Configurations={0,7813,TIMER1,F_CPU_1024,CTC_Mode};
	Timer_init(&TIMER_Configurations);
	Timer_setCallBack(Timer_CallBack,TIMER_Configurations.timer_ID);

	/* Initialize the PWM driver */
	PWM_Timer0_Start();/* Initialize the PWM driver */
	PWM_Timer0_Start();

	/* Initialize the UART driver */
	UART_ConfigType UART_Configurations = {EIGHT_BIT,Disabled,ONE_BIT,BaudRate3};
	UART_init(&UART_Configurations);

	/* Initialize the TWI/I2C driver */
	TWI_ConfigType TWI_Configurations={my_address,rate_400khz};
	TWI_init(&TWI_Configurations);

	/* Initialize the MOTOR driver */
	DcMotor_Init();

	/* Initialize the PIR driver */
	PIR_init();

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	UART_sendByte(READY);

    while(1)
    {
		switch (UART_recieveByte()) {
		case EEPROM_SAVE_PASSWORD:
			EEPROM_save_pass();
			break;
		case ENTER_PASSWORD:
			Recive_password();
			if (compare_password())
			{
				while (UART_recieveByte() != READY) {}
				UART_sendByte(MATCHED);
			}
			else
			{
				while (UART_recieveByte() != READY) {}
				UART_sendByte(UNMATCHED);
			}
			break;
		case DOOR_OPEN:
			open_Door();
			break;
		case BUZZER_ON:

			seconds = 0;
			Buzzer_on();
			while (seconds < 60);
			UART_sendByte(BUZZER_OFF);
			Buzzer_off();
			break;
		}
    }
}

/*******************************************************************************/
/*                                Functions                                    */
/*******************************************************************************/

void Timer_CallBack(void)
{
	seconds ++;
}

void Recive_password(void)
{
	uint8 i;
	UART_sendByte(READY);
    for (i=0;i<PASSWORD_MAX_SIZE;i++)
    {
    	password2[i] = UART_recieveByte();
    	 _delay_ms(350);
    }
}

uint8 compare_password(void)
{
	for (uint8 i = 0; i < PASSWORD_MAX_SIZE; i++)
	{
		EEPROM_readByte( PASSWORD_ADDRESS+i , &password1[i]);
		_delay_ms(10);
		if(password1[i] != password2[i])
		{
			return UNMATCHED;
		}
	}
	return MATCHED;
}


void EEPROM_save_pass(void)
{
	uint8 i;
	UART_sendByte(READY);
	for (i = 0; i < PASSWORD_MAX_SIZE; i++) {
		EEPROM_writeByte((PASSWORD_ADDRESS+ i), UART_recieveByte());
		_delay_ms(10);
	}
}

void open_Door(void)
{
	seconds = 0;
	DcMotor_Rotate(CW,100);
	while (seconds < 15);

    UART_sendByte(DOOR_OPEN);

	while(UART_recieveByte()!=DOOR_STOP){};
	DcMotor_Rotate(STOP,0);
	_delay_ms(1000);
	while(PIR_getState()){};
	UART_sendByte(DOOR_STOP);

	while(UART_recieveByte()!=DOOR_CLOSE){};
	seconds = 0;
	DcMotor_Rotate(A_CW,100);
	while (seconds < 15);

	DcMotor_Rotate(STOP,0);
	UART_sendByte(DOOR_CLOSE);
}
