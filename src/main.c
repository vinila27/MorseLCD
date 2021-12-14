#include "lcd.h"
#include "comm.h"
#include "button.h"
#include "main.h"
//Note to User: Please modify the userconfig.h file to fit your setup before operating.

//TODO:
//	Improve conversion of overflow 'time' to real time
//  Prescalar macrofunction to allow defines to work properly ()
int main(void)
{
	initialiseLCD();
	initialiseUART();
	initialiseButton();

	while(1){
		morseProg();
		//terminalProg();
	}

}


