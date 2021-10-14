#include "lcd.h"
#include "comm.h"
//Note to User: Please modify the userconfig.h file to fit your setup before operating.

/*Current Bugs:
	- LCD::isBusy() not working properly in 4bit mode. For some reason when trying to read the busyflag from the LCD, it just reads the previously
	  sent value in DB7
	- Setting the UBBR register isn't working quite right. Hardcoded atm. Figure out, then consider the possibility of including a prescaler factor?
 TODO:
	- LCD::clearScreen()
	- LCD::nextLine()
	- LCD::backSpace() ascii 0x08 currently shows a character. Can we delete most recent entry in DRAM
*/

int main(void)
{
	initialiseLCD();
	initialiseUART();
	//enterString((const uint8_t*)"Inverse square matrix");
	//enterLetter('H');
	uint8_t rxData;
    while(1){
		rxData = receiveUART();
		enterLetter(rxData);
    }
}