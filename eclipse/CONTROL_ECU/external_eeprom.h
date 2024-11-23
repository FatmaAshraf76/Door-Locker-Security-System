#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SERIAL_CLOCK_LINE_PORT_ID            PORTC_ID
#define SERIAL_CLOCK_LINE_PIN_ID             PIN0_ID

#define SERIAL_DATA_LINE_PORT_ID             PORTD_ID
#define SERIAL_DATA_LINE_PIN_ID              PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
 
#endif /* EXTERNAL_EEPROM_H_ */
