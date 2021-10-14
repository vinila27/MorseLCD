#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "userconfig.h"
#include <avr/io.h>
#include <util/delay.h>

//Operating Command Codes (LCD datasheet)
#define CLEAR_DISP 0x01
#define RETURN_HOME 0x02
#define NOSHIFT_DISPLAY 0x06
#define DISPLAY_ON_CURSOR_ON 0x0E
#define DISPLAY_ON_CURSOR_OFF 0x0C
#define DISPLAY_OFF 0x08
#define OPERATE_4BIT_1LINE 0x20
#define OPERATE_4BIT_2LINES 0x28
#define OPERATE_8BIT_1LINE 0x30
#define OPERATE_8BIT_2LINES 0x38

//LCD Methods
void toggleEnable();
void setDataDirection(uint8_t direction); //arg direction can be 'i' or 'o' depending on whether the bus is being configured as input or output
void setAddressCounter(uint8_t address);
uint8_t getAddressDDRAM();
void writeToPorts(const uint8_t data);
void enterCommand(const uint8_t cmd);
void enterLetter(const uint8_t letter);
void enterString(const uint8_t string[]); 
void initialiseLCD();
uint8_t isBusy();

#endif /* LCD_H */
