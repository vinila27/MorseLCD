#include "comm.h"

void initialiseUART(){
	CLKPR &= ~((1 << CLKPS3)|(1 << CLKPS2)|(1 << CLKPS1)|(1 <<CLKPS0)); //Set clock prescaler to 1. Can change later. Just want to secure CLK freq
	UBRR0H = 1;//(uint8_t)((VAL_UBBR) >> 8);
	UBRR0L = 159;//(uint8_t)VAL_UBBR;
	UCSR0B |= ((1 << RXEN0)|(1 << TXEN0));
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= ((1 << UCSZ01)|(1 << UCSZ00));
	UCSR0C &= ~((1 << UMSEL01)|(1 << UMSEL00)|(1 << UCPOL0)|(1 << USBS0)); //Asynchronous mode. 1 Stop bit
	//Use no parity for now. Can add later (UCSROC)	
}

uint8_t receiveUART(){
	while(!(UCSR0A & (1 << RXC0))); //Receive buffer is Empty
	return UDR0;
}

void transmitUART(const uint8_t data){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
		
}
	

