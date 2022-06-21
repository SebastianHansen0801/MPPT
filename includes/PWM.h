/*
 * PWM.h
 *
 * Created: 06-05-2021 14:16:17
 *  Author: sebas
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdbool.h>

void initFastPWM0(unsigned char compVal);  // initialize fast PWM with timer0
void initPhasePWM0(unsigned char compVal); // initialize phase correct PWM with timer0

// initialize fast PWM 1
void initFastPWM1(unsigned int compVal, unsigned int prescalerVal, bool reverse);
// initialize phase correct PWM 1
void initPhasePWM1(unsigned int compVal, unsigned int prescalerVal, bool reverse);
// initialize phase and frequency correct PWM 1
void initPhaseFreqPWM1(unsigned int compVal, unsigned int topVal, unsigned int prescalerVal, bool reverse);

// initialize fast PWM 3
void initFastPWM3(unsigned int compVal, unsigned int prescalerVal, bool reverse);
// initialize phase correct PWM 3
void initPhasePWM3(unsigned int compVal, unsigned int prescalerVal, bool reverse);
// initialize phase and frequency correct PWM 3
void initPhaseFreqPWM3(unsigned int compVal, unsigned int topVal, unsigned int prescalerVal, bool reverse);

// initialize fast PWM 4
void initFastPWM4(unsigned int compVal, unsigned int prescalerVal, bool reverse);
// initialize phase correct PWM 4
void initPhasePWM4(unsigned int compVal, unsigned int prescalerVal, bool reverse);
// initialize phase and frequency correct PWM 4
void initPhaseFreqPWM4(unsigned int compVal, unsigned int topVal, unsigned int prescalerVal, bool reverse);

// initialize fast PWM 5
void initFastPWM5(unsigned int compVal, unsigned int prescalerVal, bool reverse);
// initialize phase correct PWM 5
void initPhasePWM5(unsigned int compVal, unsigned int prescalerVal, bool reverse);
// initialize phase and frequency correct PWM 5
void initPhaseFreqPWM5(unsigned int compVal, unsigned int topVal, unsigned int prescalerVal, bool reverse);

void updatePWM(char timer, unsigned int compVal);

#endif /* PWM_H_ */