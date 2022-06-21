/*
 * timer.c
 *
 * Created: 25-03-2021 14:22:37
 * Author : sebas
 */ 
#ifndef __AVR_ATmega2560__
    #define __AVR_ATmega2560__
#endif

#include <avr/io.h>
void initTimer1CTC(unsigned int compareValue, unsigned int prescaleValue) {
	//set prescale value
	switch (prescaleValue) {
		case 0:
			TCCR1B |=(0<<CS12)|(0<<CS11)|(0<<CS10);
			break;
		case 8:
			TCCR1B |=(0<<CS12)|(1<<CS11)|(0<<CS10);
			break;
		case 64:
			TCCR1B |=(0<<CS12)|(1<<CS11)|(1<<CS10);
			break;
		case 256:
			TCCR1B |=(1<<CS12)|(0<<CS11)|(0<<CS10);
			break;
		case 1024:
			TCCR1B |=(1<<CS12)|(0<<CS11)|(1<<CS10);
			break;
		default:
			TCCR1B |=(0<<CS12)|(0<<CS11)|(0<<CS10);
			break;
			
	}
	TCCR1B |=(1<<WGM12); //CTC mode
	OCR1A =compareValue;
	TIMSK1 |=(1<<OCIE1A); //interupt enable
}

void initTimer3CTC(unsigned int compareValue, unsigned int prescaleValue) {
	//set prescale value
	switch (prescaleValue) {
		case 0:
		TCCR3B |=(0<<CS32)|(0<<CS31)|(0<<CS30);
		break;
		case 8:
		TCCR3B |=(0<<CS32)|(1<<CS31)|(0<<CS30);
		break;
		case 64:
		TCCR3B |=(0<<CS32)|(1<<CS31)|(1<<CS30);
		break;
		case 256:
		TCCR3B |=(1<<CS32)|(0<<CS31)|(0<<CS30);
		break;
		case 1024:
		TCCR3B |=(1<<CS32)|(0<<CS31)|(1<<CS30);
		break;
		default:
		TCCR3B |=(0<<CS32)|(0<<CS31)|(0<<CS30);
		break;
		
	}
	TCCR3B |=(1<<WGM32); //CTC mode
	OCR3A =compareValue;
	TIMSK3 |=(1<<OCIE3A); //interupt enable
}

void initTimer4CTC(unsigned int compareValue, unsigned int prescaleValue) {
	//set prescale value
	switch (prescaleValue) {
		case 0:
		TCCR4B |=(0<<CS42)|(0<<CS41)|(0<<CS40);
		break;
		case 8:
		TCCR4B |=(0<<CS42)|(1<<CS41)|(0<<CS40);
		break;
		case 64:
		TCCR1B |=(0<<CS42)|(1<<CS41)|(1<<CS40);
		break;
		case 256:
		TCCR4B |=(1<<CS42)|(0<<CS41)|(0<<CS40);
		break;
		case 1024:
		TCCR4B |=(1<<CS42)|(0<<CS41)|(1<<CS40);
		break;
		default:
		TCCR4B |=(0<<CS42)|(0<<CS41)|(0<<CS40);
		break;
		
	}
	TCCR4B |=(1<<WGM42); //CTC mode
	OCR4A =compareValue;
	TIMSK4 |=(1<<OCIE4A); //interupt enable
}

void initTimer1Overflow(unsigned int startVal, unsigned int prescaleValue) {
	//set prescale value
	switch (prescaleValue) {
		case 0:
		TCCR1B |=(0<<CS12)|(0<<CS11)|(0<<CS10);
		break;
		case 8:
		TCCR1B |=(0<<CS12)|(1<<CS11)|(0<<CS10);
		break;
		case 64:
		TCCR1B |=(0<<CS12)|(1<<CS11)|(1<<CS10);
		break;
		case 256:
		TCCR1B |=(1<<CS12)|(0<<CS11)|(0<<CS10);
		break;
		case 1024:
		TCCR1B |=(1<<CS12)|(0<<CS11)|(1<<CS10);
		break;
		default:
		TCCR1B |=(0<<CS12)|(0<<CS11)|(0<<CS10);
		break;
		
	}
	TCNT1 = startVal;
	TIMSK1 |=(1<<TOIE1); //enable overflow interupt
}

void initTimer3Overflow(unsigned int startVal, unsigned int prescaleValue) {
	//set prescale value
	switch (prescaleValue) {
		case 0:
		TCCR3B |=(0<<CS32)|(0<<CS31)|(0<<CS30);
		break;
		case 8:
		TCCR3B |=(0<<CS32)|(1<<CS31)|(0<<CS30);
		break;
		case 64:
		TCCR3B |=(0<<CS32)|(1<<CS31)|(1<<CS30);
		break;
		case 256:
		TCCR3B |=(1<<CS32)|(0<<CS31)|(0<<CS30);
		break;
		case 1024:
		TCCR3B |=(1<<CS32)|(0<<CS31)|(1<<CS30);
		break;
		default:
		TCCR3B |=(0<<CS32)|(0<<CS31)|(0<<CS30);
		break;
		
	}
	TCNT3 = startVal;
	TIMSK3 |=(1<<TOIE3); //enable overflow interupt
}

void initTimer4Overflow(unsigned int startVal, unsigned int prescaleValue) {
	//set prescale value
	switch (prescaleValue) {
		case 0:
		TCCR4B |=(0<<CS42)|(0<<CS41)|(0<<CS40);
		break;
		case 8:
		TCCR4B |=(0<<CS42)|(1<<CS41)|(0<<CS40);
		break;
		case 64:
		TCCR1B |=(0<<CS42)|(1<<CS41)|(1<<CS40);
		break;
		case 256:
		TCCR4B |=(1<<CS42)|(0<<CS41)|(0<<CS40);
		break;
		case 1024:
		TCCR4B |=(1<<CS42)|(0<<CS41)|(1<<CS40);
		break;
		default:
		TCCR4B |=(0<<CS42)|(0<<CS41)|(0<<CS40);
		break;
		
	}
	TCNT4 = startVal;
	TIMSK4 |=(1<<TOIE4); //enable overflow interupt
}
