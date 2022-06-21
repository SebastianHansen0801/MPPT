/*
 * CTCtimer.h
 *
 * Created: 25-03-2021 15:17:05
 *  Author: sebas
 */ 


#ifndef CTCTIMER_H_
#define CTCTIMER_H_

void initTimer1CTC(unsigned int compareValue, unsigned int prescaleValue); //initialize timer1 in CTC mode
void initTimer3CTC(unsigned int compareValue, unsigned int prescaleValue); //initialize timer3 in CTC mode
void initTimer4CTC(unsigned int compareValue, unsigned int prescaleValue); //initialize timer4 in CTC mode


//remember to set TCNTn in the ISR
void initTimer1Overflow(unsigned int startVal, unsigned int prescaleValue); //initialize timer1 in normal (overflow) mode
void initTimer3Overflow(unsigned int startVal, unsigned int prescaleValue); //initialize timer3 in normal (overflow) mode
void initTimer4Overflow(unsigned int startVal, unsigned int prescaleValue); //initialize timer4 in normal (overflow) mode



#endif /* CTCTIMER_H_ */