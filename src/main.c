#include "main.h"
//Note to User: Please modify the userconfig.h file to fit your setup before operating.

//TODO:
//	Improve conversion of overflow 'time' to real time
//  Prescalar macrofunction to allow defines to work properly ()
//  Userconfig macro to select which main() function to invoke
//  Consider seperating timing of button presses from debounceButton() into a separately called function.
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


