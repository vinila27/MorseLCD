#include "lcd.h"
#include "comm.h"
//Note to User: Please modify the userconfig.h file to fit your setup before operating.

/*Current Bugs:
	- Setting the UBBR register isn't working quite right. Hardcoded atm. Figure out, then consider the possibility of including a prescaler factor?
 TODO:
	- LCD::clearScreen()
	- LCD::nextLine()
*/
/*
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "userconfig.h"
#include "lcd.h"
#include "comm.h"*/

int main(void)
{
	//DDRB |= (1 << PB4);
	initialiseLCD();
	initialiseUART();
	uint8_t rxData;
	uint8_t address;
	//uint8_t ubbr_lower = (uint8_t)VAL_UBBR;
	//uint8_t ubbr_upper = (uint8_t)((uint16_t)(VAL_UBBR) >> 8);
    while(1){
		rxData = receiveUART();
		enterLetter(rxData);
		//transmitUART(rxData);
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

	/*while(1){
		PORTB |= (1 << PB4);
		_delay_ms(1000);
		PORTB &= ~(1 << PB4);
		_delay_ms(1000);
	}*/
}


