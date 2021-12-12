#include "button.h"
#include "lcd.h"

volatile static uint16_t pressTime = 0;
uint8_t morseLetter = 0; 

static inline void debounceButton();

//Should be called every ~4ms
ISR(TIMER1_OVF_vect){
    debounceButton();
}

void initialiseButton(){
    DDR_BUTTON &= ~(1 << PNUM_BUTTON); //Set button pin as input
    //Activate internal pull-up. 
    PORT_BUTTON |= (1 << PNUM_BUTTON);
    //NB: Pins are active low

    //Setup timer 1. No prescalar, and ovf interrupt enabled.
    TCCR1B |= (1 << CS10);
    TCCR1B &= ~((1 << CS11)|(1 << CS12));
    TIMSK1 |= (1 << TOIE1);
}

void checkButton(){
    static pressCount = 0;
    //Check if button has been pressed (i.e. there is value in pressTime)
    if(pressTime != 0){
        if(pressTime*4UL <= T_THRESHOLD){
            //Consider it a 'press'. Encode as a '0' (i.e. do nothing)
        }
        else{
            //Consider it a 'hold'. Encode as a '1'
            morseLetter += (1 << pressCount);
        }
    pressTime = 0;
    }
    if(++pressCount >= 3){
        pressCount = 0;
        //convert to ASCII
        //enterLetter();
    }
}

uint8_t morseToASCII(uint8_t code){

}


static inline void debounceButton(){
    static uint8_t buttonState = 0;
    static uint8_t buttonCount = 0;
    static uint16_t time = 0;
    ++time;

    uint8_t stateCurrent = ((~PIN_BUTTON & BUTTON_MSK) != 0); //invert reg as active low
    if(stateCurrent != buttonState){
        if(++buttonCount >= 4 && !buttonState){ 
            buttonState = stateCurrent;
            buttonCount = 0;
            time = 0;
        }
        else if(++buttonCount >= 4 && buttonState){
            buttonState = stateCurrent;
            buttonCount = 0;
            pressTime = time;
        }
    }
    else{
        return;
    }
}