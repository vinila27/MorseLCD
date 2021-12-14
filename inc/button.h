#ifndef _BUTTON_
#define _BUTTON_

#define T_THRESHOLD 500UL //Time boundary (ms) between a button 'press' and 'hold'
#define T_TIMEOUT 5000UL //Time limit (ms) after which the morse stream is closed and a conversion is made
#define T_ITERATIONS (uint16_t) T_TIMEOUT/33UL //Number of overflow iterations before T_TIMEOUT is reached

#include <avr/interrupt.h>
#include <avr/pgmspace.h> 
#include "userconfig.h"

void initialiseButton();
void checkButton();
uint8_t morseToASCII(uint8_t code);


#endif /* _BUTTON_ */
