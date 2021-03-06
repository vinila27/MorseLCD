#include "lcd.h"

static uint8_t initialised = 0; //LCD Busy flag can only be checked after intialised. This flag indicates when this is so.
static uint8_t timeSensitive = 1; //flag used when initialising 4-bit bus. Required to ensure correct timing for first step.

//Toggles the Enable pin which is required for sending commands to the LCD
//Liberal Timing applied with respect to datasheet (pg. 52)
void toggleEnable(){
	PORT_EN &= ~(1 << PNUM_EN);
	_delay_us(1);
	PORT_EN |= (1 << PNUM_EN);
	_delay_us(1);
	PORT_EN &= ~(1 << PNUM_EN);
	_delay_us(100);
}
//Sets the Databus to either input or output mode depending on 'direction' variable being 'i' or 'o'
void setBusDirection(const uint8_t direction){
	switch(direction){
		case 'i':
			DDR_D7 &= ~(1 << PNUM_D7);
			DDR_D6 &= ~(1 << PNUM_D6);
			DDR_D5 &= ~(1 << PNUM_D5);
			DDR_D4 &= ~(1 << PNUM_D4);
			switch(DATABUS_SIZE){
				case 8:
				DDR_D3 &= ~(1 << PNUM_D3);
				DDR_D2 &= ~(1 << PNUM_D2);
				DDR_D1 &= ~(1 << PNUM_D1);
				DDR_D0 &= ~(1 << PNUM_D0);
				break;
			}
			break;
		case 'o':
			DDR_D7 |= (1 << PNUM_D7);
			DDR_D6 |= (1 << PNUM_D6);
			DDR_D5 |= (1 << PNUM_D5);
			DDR_D4 |= (1 << PNUM_D4);
			switch(DATABUS_SIZE){
				case 8:
				DDR_D3 |= (1 << PNUM_D3);
				DDR_D2 |= (1 << PNUM_D2);
				DDR_D1 |= (1 << PNUM_D1);
				DDR_D0 |= (1 << PNUM_D0);
				break;
			}
			break;
	}
	
}

//Used to change the address counter for DDRAM if you wish to write at particular location on LCD (pg 29 of datasheet)
void setAddressCounter(const uint8_t address){
	PORT_RS &= ~(1 << PNUM_RS);
	PORT_RW &= ~(1 << PNUM_RW);
	writeToPorts(address);
	PORT_D7 |= (1 << PNUM_D7); //Overwrite D7 to high to write ddram address
	toggleEnable();
	switch(DATABUS_SIZE){
		case 4:
			writeToPorts(address << 4);
			toggleEnable();	
			break;
	}
}

//Used to read the DDRAM address counter (pg 29 of datasheet)
uint8_t getAddressDDRAM(){
	uint8_t address = 0;
	setBusDirection('i');
	PORT_RS &= ~(1 << PNUM_RS);
	PORT_RW |= (1 << PNUM_RW);
	PORT_EN |= (1 << PNUM_EN);
	_delay_us(1); // Need to wait 160ns before reading data 
	address += (((PIN_D6 & (1 << PNUM_D6)) >> PNUM_D6) << 6);
	address += (((PIN_D5 & (1 << PNUM_D5)) >> PNUM_D5) << 5);
	address += (((PIN_D4 & (1 << PNUM_D4)) >> PNUM_D4) << 4);
	switch(DATABUS_SIZE){
		case 8:
			address += (((PIN_D3 & (1 << PNUM_D3)) >> PNUM_D3) << 3);
			address += (((PIN_D2 & (1 << PNUM_D2)) >> PNUM_D2) << 2);
			address += (((PIN_D1 & (1 << PNUM_D1)) >> PNUM_D1) << 1);
			address += (((PIN_D0 & (1 << PNUM_D0)) >> PNUM_D0));
			break;
		case 4:
			PORT_EN &= ~(1 << PNUM_EN);
			_delay_us(1);
			PORT_EN |= (1 << PNUM_EN);
			_delay_us(1);
			address += (((PIN_D7 & (1 << PNUM_D7)) >> PNUM_D7) << 3);
			address += (((PIN_D6 & (1 << PNUM_D6)) >> PNUM_D6) << 2);
			address += (((PIN_D5 & (1 << PNUM_D5)) >> PNUM_D5) << 1);
			address += (((PIN_D4 & (1 << PNUM_D4)) >> PNUM_D4));
			break;
	}
	PORT_EN &= ~(1 << PNUM_EN);
	setBusDirection('o');
	return address;
}

//Used to write data to the mcu databus output registers
void writeToPorts(const uint8_t data){
	PORT_D7 = (PORT_D7 & ~(1 << PNUM_D7)) | (((data & 0x80) >> 7) << PNUM_D7);
	PORT_D6 = (PORT_D6 & ~(1 << PNUM_D6)) | (((data & 0x40) >> 6) << PNUM_D6);
	PORT_D5 = (PORT_D5 & ~(1 << PNUM_D5)) | (((data & 0x20) >> 5) << PNUM_D5);
	PORT_D4 = (PORT_D4 & ~(1 << PNUM_D4)) | (((data & 0x10) >> 4) << PNUM_D4);
	switch(DATABUS_SIZE){
		case 8:
			PORT_D3 = (PORT_D3 & ~(1 << PNUM_D3)) | (((data & 0x08) >> 3) << PNUM_D3);
			PORT_D2 = (PORT_D2 & ~(1 << PNUM_D2)) | (((data & 0x04) >> 2) << PNUM_D2);
			PORT_D1 = (PORT_D1 & ~(1 << PNUM_D1)) | (((data & 0x02) >> 1) << PNUM_D1);
			PORT_D0 = (PORT_D0 & ~(1 << PNUM_D0)) | ((data & 0x01) << PNUM_D0);
			break;
	}
}

//Used to tinker with LCD settings (i.e. Both RW and RS pins set low). See pg 24 of Datasheet.
void enterCommand(const uint8_t cmd){
	if(initialised){
		while(isBusy());
	}
	writeToPorts(cmd);
	PORT_RS &= ~(1 << PNUM_RS);
	PORT_RW &= ~(1 << PNUM_RW);
	toggleEnable();
	switch(DATABUS_SIZE){
		case 4:
			if(timeSensitive){
				_delay_ms(4.1);
			}
			writeToPorts(cmd << 4);		
			toggleEnable();
			break;
	}
}
//Accepts ASCII 'letter' input and writes to LCD DDRAM
void enterLetter(const uint8_t letter){
	while(isBusy()){};
	if(letter == 0x7F){ //Del code. Backspace on this laptop is mapped to del
			uint8_t address;
			address = getAddressDDRAM();
			if(address == 0x00){
				return;
			}
			setAddressCounter(address - 1); //TODO: Account for 2 line mode with disjoint mem locations
			enterLetter(0x20); //Blank character
			setAddressCounter(address - 1);
	}
	else if(letter == 0x0D){ //enter key
		setAddressCounter(0x40);
	}
	else{ //normal letters + some other irrelevant characters
		writeToPorts(letter);
		PORT_RS |= (1 << PNUM_RS);
		PORT_RW &= ~(1 << PNUM_RW);
		toggleEnable();
		switch(DATABUS_SIZE){
			case 4: //Upgrade the lower nibble to upper position and send
				writeToPorts(letter << 4);
				toggleEnable();
				break;
		}
	}
	
}

void enterString(const uint8_t string[]){
	for(int i = 0; string[i] != '\0'; i++){
		enterLetter(string[i]);
	}
}
//Steps needed to initialise 4 and 8bit mode data transfer between uC and LCD according to datasheet
void initialiseLCD(){
	DDR_RS |= (1 << PNUM_RS);
	DDR_RW |= (1 << PNUM_RW);
	DDR_EN |= (1 << PNUM_EN);
	switch(DATABUS_SIZE){ 
		case 8: //pg 45, Figure 23 of Datasheet
			setBusDirection('o');
			_delay_ms(1000);
			enterCommand(OPERATE_8BIT_2LINES);
			_delay_ms(4.1);
			enterCommand(OPERATE_8BIT_2LINES);
			_delay_us(100);
			enterCommand(OPERATE_8BIT_2LINES);
			enterCommand(OPERATE_8BIT_2LINES);
			enterCommand(DISPLAY_OFF);
			enterCommand(CLEAR_DISP);
			_delay_ms(2);
			enterCommand(NOSHIFT_DISPLAY);
			enterCommand(DISPLAY_ON_CURSOR_ON);	
			initialised = 1;
			break;
		
		case 4: //pg 46, Figure 24 of Datasheet
			setBusDirection('o');
			_delay_ms(1000);
			enterCommand(0x33); //Haven't introduced a define for 0x33 and 0x32 as they are different in 8 and 4bit mode
			timeSensitive = 0;
			enterCommand(0x32);
			enterCommand(OPERATE_4BIT_2LINES);
			enterCommand(DISPLAY_OFF);
			enterCommand(CLEAR_DISP);
			_delay_ms(2);
			enterCommand(NOSHIFT_DISPLAY);
			enterCommand(DISPLAY_ON_CURSOR_ON);
			initialised = 1;
			break;	
	}
}
//Check the status of the LCD Busy flag to see if it is ready to take instructions
uint8_t isBusy(){
	uint8_t flag = 1;
	PORT_RW |= (1 << PNUM_RW);
	PORT_RS &= ~(1 << PNUM_RS);
	PORT_EN &= ~(1 << PNUM_EN);
	setBusDirection('i');
	PORT_EN |= (1 << PNUM_EN);
	_delay_us(1); //Need to wait 160ns (t_DDR pg 52 of datasheet) before reading data
	flag = ((PIN_D7 & (1 << PNUM_D7)) >> PNUM_D7);
	PORT_EN &= ~(1 << PNUM_EN);
	switch(DATABUS_SIZE){
		case 4: //Need to toggle a second time in 4bit mode as you need to carry out the full 8bit read (pg 33 of datasheet, Figure 17)
			toggleEnable();
			break;
	}
	setBusDirection('o');
	return flag;
}
