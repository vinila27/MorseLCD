#include "lcd.h"
#include "comm.h"
//Note to User: Please modify the userconfig.h file to fit your setup before operating.

int main(void)
{
	initialiseLCD();
	initialiseUART();
	uint8_t rxData;
	uint8_t address;
   while(1){
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

}


