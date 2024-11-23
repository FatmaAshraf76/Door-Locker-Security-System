#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	FIVE_BIT,SEX_BIT,SEVEEN_BIT,EIGHT_BIT,NINE_BIT=0x7
}UART_BitDataType;

typedef enum
{
	Disabled, Even_Parity=0x2 , Odd_Parity=0x3
}UART_ParityType;

typedef enum
{
	ONE_BIT,TW0_BIT
}UART_StopBitType;

typedef enum
{
	BaudRate1=2400,BaudRate2=2800,BaudRate3=9600,BaudRate4=14400,BaudRate5=19200,BaudRate6=28800,BaudRate7=38400,BaudRate8=57600,BaudRate9=76800,BaudRate10=115200,BaudRate11=230400,BaudRate12=250000,BaudRate13=5000000,BaudRate14=1000000
}UART_BaudRateType;

typedef struct {
   UART_BitDataType bit_data;
   UART_ParityType parity;
   UART_StopBitType stop_bit;
   UART_BaudRateType baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr) ;

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
