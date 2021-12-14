#include "button.h"
#include "lcd.h"

volatile static uint16_t buttonPressTime = 0; //
volatile static uint8_t timeout = 0; //No data for at least T_TIMEOUT seconds

static inline void debounceButton();

//Should be called every ~33ms
ISR(TIMER1_OVF_vect){
    debounceButton();
}

void initialiseButton(){
    DDR_BUTTON &= ~(1 << PNUM_BUTTON); //Set button pin as input
    //Activate internal pull-up. 
    PORT_BUTTON |= (1 << PNUM_BUTTON);

    //Setup timer 1. prescalar of 8 and ovf interrupt enabled.
    TCCR1B |= (1 << CS11);
    TCCR1B &= ~((1 << CS10)|(1 << CS12));
    TIMSK1 |= (1 << TOIE1);
    sei();
    //Testing
    DDRC |= (1 << 5);
}

//Record button presses as either 'presses' (<= T_THRESHOLD s) or 'holds' (> T_THRESHOLD s)
//Presses are encoded as '0' and Holds as '1' in morseLetter.
//Presses stored in big endian format (i.e. First recorded bit stored in LSB of morseLetter)
//3 MSB will store the length of the signal (i.e. to distingush between 1 'press' and 3 'presses' which both store 0's)
void checkButton(){
    static uint8_t pressCount = 0;
    static uint8_t morseLetter = 0;
    //Check if button has been pressed (i.e. there is value in buttonPressTime)
    if(buttonPressTime != 0){
        if(buttonPressTime*33UL <= T_THRESHOLD){
            //Consider it a 'press/dot'. Encode as a '0' (i.e. do nothing)
        }
        else{
            //Consider it a 'hold/bar'. Encode as a '1'
            morseLetter |= (1 << pressCount);
        }
        buttonPressTime = 0; //reset
        ++pressCount;
    }
    //if(timeout), end the stream and convert to ASCII
    if(timeout && pressCount){
        PORTC |= (1 << 5);
        morseLetter |= (pressCount << 5); //3 MSB will store how many button presses/holds were recorded.
        pressCount = 0;
        //convert to ASCII
        enterLetter(morseToASCII(morseLetter));
        morseLetter = 0;
        timeout = 0;
    }
    //timeout, but no button press/holds. Therefore just clear timeout
    else if(timeout && !pressCount){
        timeout = 0;
    }
}

uint8_t morseToASCII(uint8_t code){
    static const uint8_t lookup[256] __attribute__((progmem)) = 
    {
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    'E' , 'T' , 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    'I' , 'N' , 'A' , 'M' , 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    'S' , 'D' , 'R' , 'G' , 'U' , 'K' , 'W' , 'O' ,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    'H' , 'B' , 'L' , 'Z' , 'F' , 'C' , 'P' , 0x20,
    'V' , 'X' , 0x20, 'Q' , 0x20, 'Y' , 'J' , 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    '5' , '6' , 0x20, '7' , 0x20, 0x20, 0x20, '8' ,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '9' ,
    '4' , 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    '3' , 0x20, 0x20, 0x20, '2' , 0x20, '1' , '0' ,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
    };    
    return lookup[code];
}

static inline void debounceButton(){
    static uint8_t buttonState = 1; //assume initially not pressed
    static uint8_t debounceIteration = 0;
    static uint16_t time = 0;
    static uint8_t changeDetected = 0;
   
    ++time;

    uint8_t stateCurrent = (((PIN_BUTTON & BUTTON_MSK) >> PNUM_BUTTON) != 0);
    //Change in Button State
    if(stateCurrent != buttonState){
        //Button Pressed
        if((++debounceIteration >= 4) && !changeDetected){ 
            buttonState = stateCurrent;
            debounceIteration = 0;
            changeDetected = 1;
            time = 0;
        }
        //Button Released
        else if((++debounceIteration >= 4) && changeDetected){
            buttonPressTime = time;
            buttonState = stateCurrent;
            debounceIteration = 0;
            changeDetected = 0;
        }
    }
    //No press for T_TIMEOUT seconds
    else if((time > T_ITERATIONS)){
        timeout = 1;
        time = 0;
    }
    else{
        return;
    }
}