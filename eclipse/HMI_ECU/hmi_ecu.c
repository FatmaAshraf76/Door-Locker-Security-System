#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "keypad.h"
#include "timer.h"
#include "lcd.h"

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
#define PIR_SENSOR             0x19
#define ENTER                  13


uint8 password1[PASSWORD_MAX_SIZE];
uint8 password2[PASSWORD_MAX_SIZE];


/* global variable contain the ticks count of the timer */
volatile uint8 seconds = 0;

uint8 try_agin=0;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer_CallBack(void);
void Send_password(uint8 *ptr);
void Enter_password(uint8 *ptr);
uint8 compare_password(uint8 *ptr1 ,uint8 *ptr2);
void Create_password(void);
void Open_Door(void);
void Chanage_Password(void);

/*******************************************************************************
 *                          main application                                   *
 *******************************************************************************/

int main(void)
{
	uint8 key_num;

	/* Initialize the Timer  driver */
	Timer_ConfigType TIMER_Configurations={0,7813,TIMER1,F_CPU_1024,CTC_Mode};
	Timer_init(&TIMER_Configurations);
	Timer_setCallBack(Timer_CallBack,TIMER_Configurations.timer_ID);

	/* Initialize the UART driver */
	UART_ConfigType UART_Configurations = {EIGHT_BIT,Disabled,ONE_BIT,BaudRate3};
	UART_init(&UART_Configurations);

	/* Initialize the LCD  driver */
	LCD_init();

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	while (UART_recieveByte() != READY);
	Create_password();

    while(1)
    {
		LCD_clearScreen();
	    LCD_displayString("+ :Open Door");
	    LCD_moveCursor(1,0);
	    LCD_displayString("- :Change Pass");

	    key_num=KEYPAD_getPressedKey();
	    _delay_ms(500);

		while (key_num!='-' && key_num!='+')
		{
			key_num=KEYPAD_getPressedKey();
			_delay_ms(500);
		}
	    if(key_num == '+')
		{
			Open_Door();
		}
		else if(key_num == '-')
		{
			Chanage_Password();
		}
    }
}



/*******************************************************************************/
/*                             Functions                                          */
/*******************************************************************************/
void Timer_CallBack(void)
{
	seconds++;
}

void Send_password(uint8 *ptr)
{
	uint8 i;
	 while (UART_recieveByte() != READY);
    for(i=0;i<PASSWORD_MAX_SIZE;i++)
    {
        UART_sendByte(ptr[i]);
        _delay_ms(350);
    }
}

void Enter_password(uint8 *ptr)
{
	uint8 i;
	uint8 key_num;
	/* Get the pressed button from keypad */
	for(i=0;i<PASSWORD_MAX_SIZE;i++)
	{
		key_num = KEYPAD_getPressedKey();
		if(key_num>=0 && key_num<=9)
		{
			LCD_displayString("*");
			ptr[i]=key_num;
			_delay_ms(350);
		}
		else
		{
			i--;
		}
	}
	/*when press enter mean finish entering the password*/
	while(KEYPAD_getPressedKey() != ENTER){};
}

uint8 compare_password(uint8 *ptr1 ,uint8 *ptr2)
{
	uint8 i;
	for(i=0;i<PASSWORD_MAX_SIZE;i++)
	{
		if(ptr1[i]!=ptr2[i])
		{
			return UNMATCHED;
		}
	}
	return MATCHED;
}


void Create_password(void)
{
	uint8 check;
	LCD_clearScreen();
	LCD_displayString("Plz enter pass:");
	LCD_moveCursor(1, 0);
	Enter_password(password1);

	LCD_clearScreen();
	LCD_displayString("PlZ re_Enter the");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass:");
	LCD_moveCursor(1,11);
	Enter_password(password2);
	LCD_clearScreen();
	check=compare_password(password1,password2);

	if (check == UNMATCHED)
	{
		LCD_displayString(" rejected ");
		_delay_ms(500);
		LCD_clearScreen();
		Create_password();
	}
	else
	{
		LCD_displayString(" accepted ");
		_delay_ms(500);
		LCD_clearScreen();
		UART_sendByte(EEPROM_SAVE_PASSWORD);
		Send_password(password1);
	}
}

void Open_Door(void)
{
	uint8 check;
	uint8 key_num;
	try_agin++;
	LCD_clearScreen();
	LCD_displayString( "plz enter Pass:");
	LCD_moveCursor(1, 0);
	Enter_password(password1);

	UART_sendByte(ENTER_PASSWORD);
	Send_password(password1);
	UART_sendByte(READY);
	check=UART_recieveByte();

	if(check == MATCHED)
	{
		UART_sendByte(DOOR_OPEN);
		seconds = 0;
		LCD_clearScreen();
		LCD_displayString("Door Unlocking..");
		while (seconds < 15);


		while (UART_recieveByte() != DOOR_OPEN){};

		UART_sendByte(DOOR_STOP);
		LCD_clearScreen();
		LCD_displayString("Wait for people");
		LCD_moveCursor(1,6);
		LCD_displayString("to Enter");
		//_delay_ms(500);
		while (UART_recieveByte() != DOOR_STOP){};

		UART_sendByte(DOOR_CLOSE);
		seconds = 0;
		LCD_clearScreen();
		LCD_displayString("Door locking.. ");
		while (seconds < 15);

		while (UART_recieveByte() != DOOR_CLOSE){};

		try_agin = 0;
		LCD_clearScreen();
	    LCD_displayString("+ :Open Door");
	    LCD_moveCursor(1,0);
	    LCD_displayString("- :Change Pass");

	    key_num=KEYPAD_getPressedKey();
	    _delay_ms(500);

		while (key_num!='-' && key_num!='+')
		{
			key_num=KEYPAD_getPressedKey();
		    _delay_ms(500);
		}
		if(key_num == '+')
		{
			Open_Door();
		}
		else if(key_num == '-')
		{
			Chanage_Password();
		}
	}
	else
	{
		if(try_agin!=PASSWORD_MAX_trial)
		{
		    LCD_clearScreen();
		    LCD_displayString("UNMATCHED");
		    _delay_ms(500);
		    Open_Door();
		}
		else if(try_agin==PASSWORD_MAX_trial)
		{
			LCD_clearScreen();
			LCD_displayString(" rejected ");
			_delay_ms(500);
			UART_sendByte(BUZZER_ON);
			seconds = 0;
			while (seconds < 60);

			while (UART_recieveByte() != BUZZER_OFF){};
			LCD_clearScreen();
			try_agin = 0;

			LCD_clearScreen();
		    LCD_displayString("+ :Open Door");
		    LCD_moveCursor(1,0);
		    LCD_displayString("- :Change Pass");

		    key_num=KEYPAD_getPressedKey();
		    _delay_ms(500);

			while (key_num!='-' && key_num!='+')
			{
				key_num=KEYPAD_getPressedKey();
				_delay_ms(350);
			}
		    if(key_num == '+')
			{
				Open_Door();
			}
			else if(key_num == '-')
			{
				Chanage_Password();
			}
		}
	}
}

void Chanage_Password(void)
{
	uint8 PASS;
	uint8 key_num;
	try_agin++;
	LCD_clearScreen();
	LCD_displayString( "plz enter Pass:");
	LCD_moveCursor(1, 0);
	Enter_password(password1);
	UART_sendByte(ENTER_PASSWORD);
	Send_password(password1);
	UART_sendByte(READY);
	PASS=UART_recieveByte();

	if(PASS == MATCHED)
	{
		Create_password();
		LCD_clearScreen();
		LCD_displayString("Password changed!");
		_delay_ms(500);
		try_agin = 0;
		LCD_clearScreen();
	    LCD_displayString("+ :Open Door");
	    LCD_moveCursor(1,0);
	    LCD_displayString("- :Change Pass");

	    key_num=KEYPAD_getPressedKey();
	    _delay_ms(500);

		while (key_num!='-' && key_num!='+')
		{
			key_num=KEYPAD_getPressedKey();
		    _delay_ms(350);
		}
		if(key_num == '+')
		{
			Open_Door();
		}
		else if(key_num == '-')
		{
			Chanage_Password();
		}
	}
	else
	{
		if(try_agin!=PASSWORD_MAX_trial)
		{
		    LCD_clearScreen();
		    LCD_displayString("UNMATCHED");
		    _delay_ms(500);
		    Chanage_Password();
		}
		else if(try_agin==PASSWORD_MAX_trial)
		{
			LCD_clearScreen();
			LCD_displayString(" rejected ");
			_delay_ms(500);
			UART_sendByte(BUZZER_ON);
			seconds = 0;
			while (seconds < 60);
			while (UART_recieveByte() != BUZZER_OFF){};
			LCD_clearScreen();
			try_agin = 0;

			LCD_clearScreen();
		    LCD_displayString("+ :Open Door");
		    LCD_moveCursor(1,0);
		    LCD_displayString("- :Change Pass");

		    key_num=KEYPAD_getPressedKey();
		    _delay_ms(500);

			while (key_num!='-' && key_num!='+')
			{
				key_num=KEYPAD_getPressedKey();
			    _delay_ms(350);
			}

		    if(key_num == '+')
			{
				Open_Door();
			}
			else if(key_num == '-')
			{
				Chanage_Password();
			}
		}
	}
}
