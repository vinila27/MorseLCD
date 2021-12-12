#ifndef _BUTTON_
#define _BUTTON_

#define T_THRESHOLD 500

#include <avr/interrupt.h>
#include "userconfig.h"

volatile static uint16_t timeReference;
volatile static uint8_t overflows;
volatile static uint8_t buttonState;
volatile static uint8_t buttonCount;

void initialiseButton();
void checkButton();
uint8_t morseToASCII(uint8_t code);

#endif /* _BUTTON_ */
