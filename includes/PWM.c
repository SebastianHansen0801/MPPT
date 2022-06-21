/*
 * PWM.c
 *
 * Created: 06-05-2021 14:15:24
 *  Author: sebas
 */
#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#include <avr/io.h>
#include <stdbool.h>
// timer 0
void initFastPWM0(unsigned char compVal) {
    DDRB |= (1 << DDB7);                                  // configure OC0A pin for output pin13
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // clear OC0A on compare match, set OC0A at BOTTOM
    TCCR0B = (1 << CS01);                                 // (non-inverting mode); enable Fast PWM and set clock pre-scaler to 8
    TCNT0 = 0;                                            // force TCNT0 to count up from 0
    OCR0A = compVal;                                      // set duty cycle, top=255
}

void initPhasePWM0(unsigned char compVal) {
    TCCR0A |= (1 << COM0A1) | (1 << WGM00); // Clear OC0A on Compare Match when up-counting. Set OC0A on Compare Match when down-counting; enable Phase Correct PWM
    TCCR0B = (1 << CS01);                   // prescalling by 8
    OCR0A = compVal;                        // set duty cycle, top=255
    TCNT0 = 0;
    DDRB |= (1 << DDB7); // configure OC0A pin for outputn, pin13
}

// timer 1
void initFastPWM1(unsigned int compVal, unsigned int prescalerVal, bool reverse) {
    DDRB |= (1 << DDB5);                                  // configure OC1A pin for output (PB5) pin11
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10); // clear OC1A on compare match, set OC1A at BOTTOM
    TCCR1B = (1 << WGM12);                                // (non-inverting mode); enable Fast PWM 10 bitTCCR1B = (1 << WGM12);
    if (reverse) {
        TCCR1A |= (1 << COM1A0);
    }
    // set prescale value
    switch (prescalerVal) {
    case 0:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    case 1:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
        break;
    case 8:
        TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
        break;
    case 64:
        TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
        break;
    case 256:
        TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    case 1024:
        TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
        break;
    default:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    }
    TCNT1 = 0;       // force TCNT1 to count up from 0
    OCR1A = compVal; // set duty cycle, top=1023
}

void initPhasePWM1(unsigned int compVal, unsigned int prescalerVal, bool reverse) {
    DDRB |= (1 << PB5);                                    // configure OC1A pin for output (PB5) pin11
    TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (1 << WGM10); // Clear OC1A on Compare Match when up-counting.
                                                           // Set OC1A on Compare Match when down-counting;
                                                           // enable phase correct PWM 10 bit
    if (reverse) {
        TCCR1A |= (1 << COM1A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    case 1:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
        break;
    case 8:
        TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
        break;
    case 64:
        TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
        break;
    case 256:
        TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    case 1024:
        TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
        break;
    default:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    }
    if (reverse) {
    }
    TCNT1 = 0;
    OCR1A = compVal; // set duty cycle, top=1023
}

void initPhaseFreqPWM1(unsigned int compVal, unsigned int topVal, unsigned int prescalerVal, bool reverse) {
    // DDRB |= (1 << PB5);      // configure OC1A pin for output (PB5) pin11
    DDRB |= (1 << PB1);      // uno
    TCCR1A |= (1 << COM1A1); // Clear OC1A on Compare Match when up-counting.
                             // Set OC1A on Compare Match when down-counting
    TCCR1B = (1 << WGM13);   // enable phase and frquence correct PWM
    if (reverse) {
        TCCR1A |= (1 << COM1A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    case 1:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
        break;
    case 8:
        TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
        break;
    case 64:
        TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
        break;
    case 256:
        TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    case 1024:
        TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
        break;
    default:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (0 << CS10);
        break;
    }
    ICR1 =
        topVal;      // top value then OC1A pin can be used   // 8bit top value=204
    OCR1A = compVal; // set duty cycle, top=204
}

// timer 3
void initFastPWM3(unsigned int compVal, unsigned int prescalerVal, bool reverse) {
    DDRE |= (1 << DDE3);                                  // configure OC3A pin for output (PE3) pin5
    TCCR3A = (1 << COM3A1) | (1 << WGM31) | (1 << WGM30); // clear OC3A on compare match, set OC3A at BOTTOM
    TCCR3B = (1 << WGM32);                                // (non-inverting mode); enable Fast PWM 10 bit
    if (reverse) {
        TCCR3A |= (1 << COM3A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    case 1:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (1 << CS30);
        break;
    case 8:
        TCCR3B |= (0 << CS32) | (1 << CS31) | (0 << CS30);
        break;
    case 64:
        TCCR3B |= (0 << CS32) | (1 << CS31) | (1 << CS30);
        break;
    case 256:
        TCCR3B |= (1 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    case 1024:
        TCCR3B |= (1 << CS32) | (0 << CS31) | (1 << CS30);
        break;
    default:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    }
    TCNT3 = 0;       // force TCNT3 to count up from 0
    OCR3A = compVal; // set duty cycle, top=1023
}

void initPhasePWM3(unsigned int compVal, unsigned int prescalerVal, bool reverse) {
    DDRE |= (1 << DDE3);                                   // configure OC3A pin for output (PE3) pin5
    TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30); // Clear OC3A on Compare Match when up-counting.
                                                           // Set OC3A on Compare Match when down-counting;
                                                           // enable phase correct PWM 10 bit
    if (reverse) {
        TCCR3A |= (1 << COM3A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    case 1:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (1 << CS30);
        break;
    case 8:
        TCCR3B |= (0 << CS32) | (1 << CS31) | (0 << CS30);
        break;
    case 64:
        TCCR3B |= (0 << CS32) | (1 << CS31) | (1 << CS30);
        break;
    case 256:
        TCCR3B |= (1 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    case 1024:
        TCCR3B |= (1 << CS32) | (0 << CS31) | (1 << CS30);
        break;
    default:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    }
    TCNT3 = 0;
    OCR3A = compVal; // set duty cycle, top=1023
}

void initPhaseFreqPWM3(unsigned int compVal, unsigned int topVal, unsigned int prescalerVal, bool reverse) {
    DDRE |= (1 << DDE3);     // configure OC3A pin for output (PE3) pin5
    TCCR3A |= (1 << COM3A1); // Clear OC3A on Compare Match when up-counting. Set OC3A on Compare Match when down-counting
    TCCR3B = (1 << WGM33);   // enable phase and frquence correct PWM
    if (reverse) {
        TCCR3A |= (1 << COM3A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    case 1:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (1 << CS30);
        break;
    case 8:
        TCCR3B |= (0 << CS32) | (1 << CS31) | (0 << CS30);
        break;
    case 64:
        TCCR3B |= (0 << CS32) | (1 << CS31) | (1 << CS30);
        break;
    case 256:
        TCCR3B |= (1 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    case 1024:
        TCCR3B |= (1 << CS32) | (0 << CS31) | (1 << CS30);
        break;
    default:
        TCCR3B |= (0 << CS32) | (0 << CS31) | (0 << CS30);
        break;
    }
    ICR3 = topVal;   //
    OCR3A = compVal; // set duty cycle
}

// timer 4
void initFastPWM4(unsigned int compVal, unsigned int prescalerVal, bool reverse) {
    DDRH |= (1 << DDH3);                                  // configure OC4A pin for output (PH3) pin6
    TCCR4A = (1 << COM4A1) | (1 << WGM41) | (1 << WGM40); // clear OC4A on compare match, set OC4A at BOTTOM
    TCCR4B = (1 << WGM42);                                // (non-inverting mode); enable Fast PWM 10 bit
    if (reverse) {
        TCCR4A |= (1 << COM4A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    case 1:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
        break;
    case 8:
        TCCR4B |= (0 << CS42) | (1 << CS41) | (0 << CS40);
        break;
    case 64:
        TCCR4B |= (0 << CS42) | (1 << CS41) | (1 << CS40);
        break;
    case 256:
        TCCR4B |= (1 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    case 1024:
        TCCR4B |= (1 << CS42) | (0 << CS41) | (1 << CS40);
        break;
    default:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    }
    TCNT4 = 0;       // force TCNT4 to count up from 0
    OCR4A = compVal; // set duty cycle, top=1024
}

void initPhasePWM4(unsigned int compVal, unsigned int prescalerVal, bool reverse) {
    DDRH |= (1 << DDH3);                                   // configure OC4A pin for output (PH3) pin6
    TCCR4A |= (1 << COM4A1) | (1 << WGM41) | (1 << WGM40); // Clear OC4A on Compare Match when up-counting.
                                                           // Set OC4A on Compare Match when down-counting;
                                                           // enable phase correct PWM 10 bit
    if (reverse) {
        TCCR4A |= (1 << COM4A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    case 1:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
        break;
    case 8:
        TCCR4B |= (0 << CS42) | (1 << CS41) | (0 << CS40);
        break;
    case 64:
        TCCR4B |= (0 << CS42) | (1 << CS41) | (1 << CS40);
        break;
    case 256:
        TCCR4B |= (1 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    case 1024:
        TCCR4B |= (1 << CS42) | (0 << CS41) | (1 << CS40);
        break;
    default:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    }
    TCNT4 = 0;
    OCR4A = compVal; // set duty cycle, top=1024
}

void initPhaseFreqPWM4(unsigned int compVal, unsigned int topVal, unsigned int prescalerVal, bool reverse) {
    DDRH |= (1 << DDH3);     // configure OC4A pin for output (PH3) pin6
    TCCR4A |= (1 << COM4A1); // Clear OC4A on Compare Match when up-counting. Set OC4A on Compare Match when down-counting
    TCCR4B = (1 << WGM43);   // enable phase and frquence correct PWM
    if (reverse) {
        TCCR4A |= (1 << COM4A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    case 1:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
        break;
    case 8:
        TCCR4B |= (0 << CS42) | (1 << CS41) | (0 << CS40);
        break;
    case 64:
        TCCR4B |= (0 << CS42) | (1 << CS41) | (1 << CS40);
        break;
    case 256:
        TCCR4B |= (1 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    case 1024:
        TCCR4B |= (1 << CS42) | (0 << CS41) | (1 << CS40);
        break;
    default:
        TCCR4B |= (0 << CS42) | (0 << CS41) | (0 << CS40);
        break;
    }
    ICR4 = topVal;   //
    OCR4A = compVal; // set duty cycle, top=204
}

// timer 5
void initFastPWM5(unsigned int compVal, unsigned int prescalerVal, bool reverse) {
    DDRL |= (1 << DDL3);                                  // configure OC5A pin for output (PL3) pin46
    TCCR5A = (1 << COM5A1) | (1 << WGM51) | (1 << WGM50); // clear OC5A on compare match, set OC5A at BOTTOM
    TCCR5B = (1 << WGM52);                                // (non-inverting mode); enable Fast PWM 10 bit
    if (reverse) {
        TCCR5A |= (1 << COM5A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    case 1:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (1 << CS50);
        break;
    case 8:
        TCCR5B |= (0 << CS52) | (1 << CS51) | (0 << CS50);
        break;
    case 64:
        TCCR5B |= (0 << CS52) | (1 << CS51) | (1 << CS50);
        break;
    case 256:
        TCCR5B |= (1 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    case 1024:
        TCCR5B |= (1 << CS52) | (0 << CS51) | (1 << CS50);
        break;
    default:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    }
    TCNT5 = 0;       // force TCNT5 to count up from 0
    OCR5A = compVal; // set duty cycle, top=1025
}

void initPhasePWM5(unsigned int compVal, unsigned int prescalerVal, bool reverse) {
    DDRL |= (1 << DDL3);                                   // configure OC5A pin for output (PL3) pin46
    TCCR5A |= (1 << COM5A1) | (1 << WGM51) | (1 << WGM50); // Clear OC5A on Compare Match when up-counting.
                                                           // Set OC5A on Compare Match when down-counting;
                                                           // enable phase correct PWM 10 bit
    if (reverse) {
        TCCR5A |= (1 << COM5A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    case 1:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (1 << CS50);
        break;
    case 8:
        TCCR5B |= (0 << CS52) | (1 << CS51) | (0 << CS50);
        break;
    case 64:
        TCCR5B |= (0 << CS52) | (1 << CS51) | (1 << CS50);
        break;
    case 256:
        TCCR5B |= (1 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    case 1024:
        TCCR5B |= (1 << CS52) | (0 << CS51) | (1 << CS50);
        break;
    default:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    }
    TCNT5 = 0;
    OCR5A = compVal; // set duty cycle, top=1025
}

void initPhaseFreqPWM5(unsigned int compVal, unsigned int topVal, unsigned int prescalerVal, bool reverse) {
    DDRL |= (1 << DDL3);     // configure OC5A pin for output (PL3) pin46
    TCCR5A |= (1 << COM5A1); // Clear OC5A on Compare Match when up-counting. Set OC5A on Compare Match when down-counting
    TCCR5B = (1 << WGM53);   // enable phase and frquence correct PWM
    if (reverse) {
        TCCR5A |= (1 << COM5A0);
    }
    switch (prescalerVal) {
    case 0:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    case 1:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (1 << CS50);
        break;
    case 8:
        TCCR5B |= (0 << CS52) | (1 << CS51) | (0 << CS50);
        break;
    case 64:
        TCCR5B |= (0 << CS52) | (1 << CS51) | (1 << CS50);
        break;
    case 256:
        TCCR5B |= (1 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    case 1024:
        TCCR5B |= (1 << CS52) | (0 << CS51) | (1 << CS50);
        break;
    default:
        TCCR5B |= (0 << CS52) | (0 << CS51) | (0 << CS50);
        break;
    }
    ICR5 = topVal;   //
    OCR5A = compVal; // set duty cycle, top=205
}

void updatePWM(char timer, unsigned int compVal) {
    switch (timer) {
    case 1:
        OCR1A = compVal; // set duty cycle, top=1023

    case 3:
        OCR3A = compVal; // set duty cycle, top=1023

    case 4:
        OCR4A = compVal; // set duty cycle, top=1023

    case 5:
        OCR5A = compVal; // set duty cycle, top=1023
    }
}