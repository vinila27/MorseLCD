#ifndef USERCONFIG_H
#define USERCONFIG_H

//User Input Fields 
//If using 4-Bit mode, you only need to change the direction and port registers suffixed with _D4,_D5,_D6, and _D7. _D0-3 can be left as is

//Data bus Size. Options: 4 or 8
#define DATABUS_SIZE 4
//uC CPU
#define F_CPU 16000000
//Baud rate for UART Serial
#define BAUD 2400

//Direction Registers. Change DDRx based on which register each data line is connected to.
#define DDR_RS DDRC
#define DDR_RW DDRC
#define DDR_EN DDRC
#define DDR_D0 DDRB
#define DDR_D1 DDRB
#define DDR_D2 DDRB
#define DDR_D3 DDRB
#define DDR_D4 DDRD
#define DDR_D5 DDRD
#define DDR_D6 DDRD
#define DDR_D7 DDRD
//Port/Output Registers. Change PORTx based on which register each data line is connected to.
#define PORT_RS PORTC
#define PORT_RW PORTC
#define PORT_EN PORTC
#define PORT_D0 PORTB
#define PORT_D1 PORTB
#define PORT_D2 PORTB
#define PORT_D3 PORTB
#define PORT_D4 PORTD
#define PORT_D5 PORTD
#define PORT_D6 PORTD
#define PORT_D7 PORTD
//Pin/Input Registers. Change PINx based on which registers each data line is connected to.
#define PIN_D0 PINB
#define PIN_D1 PINB
#define PIN_D2 PINB
#define PIN_D3 PINB
#define PIN_D4 PIND
#define PIN_D5 PIND
#define PIN_D6 PIND
#define PIN_D7 PIND
//Port Number. Please enter which number on it's respective port each line is connected to. 
#define PNUM_RS 0
#define PNUM_RW 1
#define PNUM_EN 2
#define PNUM_D0 0
#define PNUM_D1 1
#define PNUM_D2 2
#define PNUM_D3 3
#define PNUM_D4 4
#define PNUM_D5 5
#define PNUM_D6 6
#define PNUM_D7 7

#endif /* USERCONFIG_H */
