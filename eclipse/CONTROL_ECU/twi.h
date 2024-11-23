#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SERIAL_CLOCK_LINE_PORT_ID            PORTC_ID
#define SERIAL_CLOCK_LINE_PIN_ID             PIN0_ID

#define SERIAL_DATA_LINE_PORT_ID             PORTD_ID
#define SERIAL_DATA_LINE_PIN_ID              PIN7_ID


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	my_address=0x01
}TWI_AddressType;

typedef enum
{
	rate_500khz,rate_400khz=2,rate_250khz=8,rate_200khz=12,rate_160khz=17,rate_125khz=24
}TWI_BaudRateType;

typedef struct {
TWI_AddressType address;
TWI_BaudRateType bit_rate;
}TWI_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(const TWI_ConfigType * Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
