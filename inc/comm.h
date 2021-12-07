#ifndef _COMM_
#define _COMM_

#include <stdint.h>
#include <avr/io.h>
#include "userconfig.h"

#define VAL_UBBR (uint16_t)(((double)F_CPU/(16UL*BAUD)) - 1 + 0.5) //+0.5 to approximate standard rounding. Rest of formula from ATMEGA datasheet, sec: UART

//Methods
void initialiseUART();
uint8_t receiveUART();
void transmitUART(const uint8_t data);

#endif 
