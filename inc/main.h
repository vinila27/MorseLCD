#ifndef _MAIN_
#define _MAIN_

#include "lcd.h"
#include "comm.h"
#include "button.h"

static inline void terminalProg(){
	static uint8_t rxData;
	static uint8_t address;
		rxData = receiveUART();
		enterLetter(rxData);
		address = getAddressDDRAM();
		transmitUART('0'); 
		transmitUART('b');
		
		for(int i = 7; i >= 0; i--){
			if((address & (1 << i)) >> i){
				transmitUART('1');
			}
			else{
				transmitUART('0');
			}
		}
		transmitUART('\r');
		transmitUART('\n');
}

static inline void morseProg(){
    checkButton();
}

#endif 
