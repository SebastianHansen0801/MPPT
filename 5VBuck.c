#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

#define F_CPU 16000000UL

// UART parameters
#define BAUD 19200
#define MYUBRRF F_CPU / 8 / BAUD - 1
#define MYUBRRH F_CPU / 16 / BAUD - 1

// Controller parameters
#define PID_KP 480.0f
#define PID_KI 25945.9f
#define PID_KD 2.2f
#define PID_TAU 0.005f
#define PID_LIM_MIN 0.0f
#define PID_LIM_MAX 1000.0f
#define PID_LIM_MIN_INT -500000.0f
#define PID_LIM_MAX_INT 500000.0f
#define SAMPLE_FREQUENCY_S 500.0f
#define SAMPLE_TIME_S 1 / SAMPLE_FREQUENCY_S

// other params
#define TIMER_VAL 61535 // freq of 500Hz
#define BIN_TO_VOLT 0.0048875f
#define VOLTAGE_DIVIDER 4.0f
#define VOLTAGE_REF 7.0f

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>

#include "includes/ADC.h"
#include "includes/PID.h"
#include "includes/PWM.h"
#include "includes/timer.h"
#include "includes/uart.h"

volatile char ADCcomplete = 0;

void init();
int calculateRem(float number);

char buffer[30] = {'\0'};

int main() {
    /* Initialise PID controller */
    PIDController pid = {PID_KP, PID_KI, PID_KD,
                         PID_TAU, PID_LIM_MIN, PID_LIM_MAX,
                         PID_LIM_MIN_INT, PID_LIM_MAX_INT, SAMPLE_TIME_S};

    PIDController_Init(&pid);
    init();
    int ADCval = 0;
    while (1) {
        if (ADCcomplete = 1) {
            ADCcomplete = 0;
            ADCval = ADCL + (ADCH << 8);
            float voltageMeasurement = ADCval * BIN_TO_VOLT;
            voltageMeasurement *= VOLTAGE_DIVIDER;
            PIDController_Update(&pid, VOLTAGE_REF, voltageMeasurement);
            updatePWM(3, pid.out);
        }
    }
}

ISR(ADC_vect) {
    // set flag to indicate sample ready
    ADCcomplete = 1;
}

ISR(TIMER1_OVF_vect) {
    // set the vlue the timer will start the count from
    TCNT1 = TIMER_VAL;
}

ISR(USART0_RX_vect) {}

void init() {
    initOverflowInt1ADC(0);
    initTimer1Overflow(TIMER_VAL, 8);
    initPhaseFreqPWM3(500, 1000, 1, 1);
    sei();
}

int calculateRem(float number) {
    int rem = number * 10;
    rem %= 10;
    return rem;
}