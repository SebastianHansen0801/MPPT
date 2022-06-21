/*
 * main.c
 *
 * Created: 3/11/2021 2:39:42 PM
 *  Author: sebas
 */ 
#ifndef __AVR_ATmega2560__
    #define __AVR_ATmega2560__
#endif

#include <avr/io.h>

void initUsart1(unsigned int ubrr) {
	UCSR1A=(1<<U2X1);	//full duplex
	//enable receive and transmit
	UCSR1B|=(1<<RXEN1)|(1<<TXEN1);
	//frame: 1 start bit, 8 data bit, no par bit, 1 stop bit
	UCSR1C|=(1<<UCSZ10)|(1<<UCSZ11);
	//baud rate values up to 16 bit therefore two registers
	UBRR1H=(unsigned char)(ubrr>>8);
	UBRR1L=(unsigned char)ubrr;
	
	UCSR1B|=(1<<RXCIE1); //receive interupt
}


//receive function. receives a byte and returns it
char getChUSART1(void) {
	while(!(UCSR1A&(1<<RXC1)));	//wait until a character is received
	return UDR1;
}

//transmit function
void putChUSART1(char tx) {
	while(!(UCSR1A&(1<<UDRE1)));
	UDR1=tx;
}

//transmit string
void putStrUSART1(char *ptr) {
	while (*ptr) {
		putChUSART1(*ptr);
		ptr++;
	}
}

void initUsart0(unsigned int ubrr) {
	UCSR0A=(1<<U2X0);	//full duplex
	//enable receive and transmit
	UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
	//frame: 1 start bit, 8 data bit, no par bit, 1 stop bit
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
	//baud rate values up to 16 bit therefore two registers
	UBRR0H=(unsigned char)(ubrr>>8);
	UBRR0L=(unsigned char)ubrr;
	
	UCSR0B|=(1<<RXCIE0); // receive interupt
}


//receive function. receives a byte and returns it
char getChUSART0(void) {
	while(!(UCSR0A&(1<<RXC0)));	//wait until a character is received
	return UDR0;
}

//transmit function
void putChUSART0(char tx) {
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=tx;
}

//transmit string
void putStrUSART0(char *ptr) {
	while (*ptr) {
		putChUSART0(*ptr);
		ptr++;
	}
}

