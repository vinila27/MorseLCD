#ifndef _COMM_
#define _COMM_

#include <stdint.h>
#include <avr/io.h>
#include "userconfig.h"

//Value to be loaded into UBBR register to represent the comm baud rate
#define VAL_UBBR (uint16_t)(((double)F_CPU/(16UL*BAUD)) - 1 + 0.5) //+0.5 to approximate standard rounding. Rest of formula from ATMEGA datasheet, sec: UART

//Methods
void initialiseUART();
static uint8_t receiveUART() __attribute__((always_inline));
static void transmitUART(const uint8_t data) __attribute__((always_inline));


static inline uint8_t receiveUART(){
	while(!(UCSR0A & (1 << RXC0))); //Wait for Receive buffer to contain unread data
	return UDR0;
}

static inline void transmitUART(const uint8_t data){
	while(!(UCSR0A & (1 << UDRE0)));  //Wait for Transmit buffer to be ready for new data
	UDR0 = data;
}
	


#endif 
