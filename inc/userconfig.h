#ifndef USERCONFIG_H
#define USERCONFIG_H

//User Input Fields 
//If using 4-Bit mode, you only need to change the direction and port registers suffixed with _D4,_D5,_D6, and _D7. _D0-3 can be left as is

//Data bus Size. Options: 4 or 8
#define DATABUS_SIZE 4
//uC CPU frequency
#define F_CPU 16000000
//Baud rate for UART Serial Transmission
#define BAUD 2400


//Direction Registers. Change DDRx based on which register each data line is connected to.
//The button input should be connect to an external interrupt pin on your device. (Avoid using PCINTs due to bouncing)
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
#define DDR_BUTTON DDRD
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
#define PORT_BUTTON PORTD
//Pin/Input Registers. Change PINx based on which registers each data line is connected to.
#define PIN_D0 PINB
#define PIN_D1 PINB
#define PIN_D2 PINB
#define PIN_D3 PINB
#define PIN_D4 PIND
#define PIN_D5 PIND
#define PIN_D6 PIND
#define PIN_D7 PIND
#define PIN_BUTTON PIND
//Port Number. Please enter which number on it's respective port each line is connected to. 
#define PNUM_RS 0
#define RS_MSK (1 << PNUM_RS)
#define PNUM_RW 1
#define RW_MSK (1 << PNUM_RW)
#define PNUM_EN 2
#define EN_MSK (1 << PNUM_EN)
#define PNUM_D0 0
#define D0_MSK (1 << PNUM_D0)
#define PNUM_D1 1
#define D1_MSK (1 << PNUM_D1)
#define PNUM_D2 2
#define D2_MSK (1 << PNUM_D2)
#define PNUM_D3 3
#define D3_MSK (1 << PNUM_D3)
#define PNUM_D4 4
#define D4_MSK (1 << PNUM_D4)
#define PNUM_D5 5
#define D5_MSK (1 << PNUM_D5)
#define PNUM_D6 6
#define D6_MSK (1 << PNUM_D6)
#define PNUM_D7 7
#define D7_MSK (1 << PNUM_D7)
#define PNUM_BUTTON 3
#define BUTTON_MSK (1 << PNUM_BUTTON)

#endif 
