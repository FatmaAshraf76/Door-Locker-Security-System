#ifndef BUZZER_H_
#define BUZZER_H_


#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* BUZZER HW Ports and Pins Ids */
#define BUZZER_PORT_ID                 PORTC_ID
#define BUZZER_PIN_ID                  PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initializes the buzzer pin direction and turn off the buzzer.
 */
 void Buzzer_init(void);

 /*
  * Description :
  * Function responsible for  Activates the buzzer.
  */
 void Buzzer_on(void);

  /*
   * Description :
   * Function responsible for  Deactivates the buzzer.
   */
 void Buzzer_off(void);


#endif /* BUZZER_H_ */
