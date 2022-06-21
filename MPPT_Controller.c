// #ifndef __AVR_ATmega2560__
// #define __AVR_ATmega2560__
// #endif

#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif

#define F_CPU 16000000UL
#define BAUD 19200
#define MYUBRRF F_CPU / 8 / BAUD - 1
#define MYUBRRH F_CPU / 16 / BAUD - 1

#define BIN_TO_VOLT 0.0048828f
#define TIMER_VAL 65135 // freq of 5kHz
#define RESISTANCE 0.1f
#define VOLTAGE_FACTOR 5.0f
#define CURRENT_FACTOR 1.0 / 83.0f
#define VOLTAGE_REF 5.0f

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>

#include "includes/ADC.h"
#include "includes/PWM.h"
// #include "includes/timer.h"
#include "includes/uart.h"

typedef enum { voltageMes,
               currentMes,
               idle } measurementType;

volatile measurementType measurement = 0;
int ADCval = 0;

char text[10] = "test";

void init();
void toogleADC();

float MPPT_calc(float voltage, float current) {
    static float prevPower = 0;
    static float prevVoltage = 0;
    static float prevOut = 500;
    static float pwmStep = 10;

    float power = voltage * current;
    float deltaPower = power - prevPower;
    float deltaVoltage = voltage - prevVoltage;

    char dir = 0;

    if (deltaPower > 0) {
        if (deltaVoltage > 0) {
            // increase voltage
            dir = 1;
        } else {
            // decrease voltage
            dir = -1;
        }
    } else {
        if (voltage > 0) {
            // decrease voltage
            dir = -1;
        } else {
            // increase voltage
            dir = 1;
        }
    }

    float out = prevOut - (dir * pwmStep);

    if (out > 900) {
        out = 900;
    } else if (out < 100) {
        out = 100;
    }

    prevPower = power;
    prevVoltage = voltage;
    prevOut = out;

    /* Return controller output */
    return out;
}

int main() {
    init();
    float voltage, current = 0;
    startADCconversion();
    while (1) {
        if (measurement == voltageMes) {
            // TODO Calculate voltage
            voltage = ADCval * BIN_TO_VOLT;
            voltage *= VOLTAGE_FACTOR;
            measurement = idle;

        } else if (measurement == currentMes) {
            // TODO Calculate current

            current = ADCval * BIN_TO_VOLT;
            current *= CURRENT_FACTOR;
            current /= RESISTANCE;

            updatePWM(1, MPPT_calc(voltage, current));

            measurement = idle;
        }
    }
}

ISR(ADC_vect) {
    PORTB ^= (1 << PB5);
    ADCval = ADCL + (ADCH << 8);
    toogleADC();
    startADCconversion();
}

// ISR(USART0_RX_vect) {
// }

void init() {
    initSingleConversionADC(0);
    startADCconversion();
    initPhaseFreqPWM1(500, 1000, 1, 1);
    // initUsart0(MYUBRRF);
    sei();

    DDRB |= (1 << PB5);
}

void toogleADC() {
    switch (ADMUX) {
    case 0x40:
        measurement = voltageMes;
        ADMUX = 0x41;
        break;
    case 0x41:
        measurement = currentMes;
        ADMUX = 0x40;
        break;
    default:
        // Default code
        break;
    }
}
