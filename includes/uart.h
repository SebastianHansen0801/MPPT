/*
 * uart.h
 *
 * Created: 11-03-2021 16:19:25
 *  Author: sebas
 */ 


//#define F_CPU 16000000UL
//#define BAUD 19200
//#define MYUBRRF F_CPU/8/BAUD-1
//#define MYUBRRH F_CPU/16/BAUD-1

#ifndef UART_H_
#define UART_H_

void initUsart0(unsigned int ubrr); //initialize uart0
char getChUSART0(void); //function to get a character. only relevant without interupt
void putChUSART0(char tx);
void putStrUSART0(char *ptr); //function to send a string

void initUsart1(unsigned int ubrr); //initialize uart0
char getChUSART1(void); //function to get a character. only relevant without interupt
void putChUSART1(char tx); //function to send a charcter
void putStrUSART1(char *ptr); //function to send a string

#endif /* UART_H_ */