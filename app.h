/* 
 * File: app.h
 * Author: Dr. Edras Pacola
 * Comments: Example App header file for Simple Task Manager implementation
 * Revision history: 
 */

#ifndef _APP_H
#define	_APP_H

#include <xc.h> // include processor files - each processor file is guarded. 

#define LED_TOGGLE_TIME     500   // time to toggle on board LED
#define PRINT_COUNTER_TIME  1000  // Print on UART 

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void toggleLed(void);
void printCounter(void);
void printWelcome(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _APP_H */

