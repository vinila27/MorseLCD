#ifndef COMM_H_
#define COMM_H_

#include <avr/io.h>
#include "userconfig.h"

#define VAL_UBBR (F_CPU/(16UL*BAUD)+0.5) - 1 //+0.5 to approximate standard rounding. Rest of formula from datasheet, sec: UART

//Methods
void initialiseUART();
uint8_t receiveUART();
void transmitUART(const uint8_t data);


#endif 