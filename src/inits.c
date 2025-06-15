#include "defines.h"

#include <stdint.h>
#include <avr/io.h>

void init_output(volatile uint8_t* ddrx_p, uint8_t pin) {
    *ddrx_p |= (1 << pin);  // set led pin as output
}

void init_input(volatile uint8_t* portx_p, uint8_t pin) {
    *portx_p |= (1 << pin);  // turn on pull-up resistor
}

void init_timer0_counter(void) {
    TCCR0B |= TIMER_PRESCALER;
}

void init_timer1_PWM(void) {
    TCCR1A |= (
        (1 << COM1A1) |  // non-inverting PWM (OCR1A)
        (1 << COM1B1) |  // non-inverting PWM (OCR1B)
        (1 << WGM10) | (1 << WGM11)  // set 10-bit fast PWM mode
    );

    TCCR1B |= (
        (1 << WGM12) | // set 10-bit fast PWM mode
        (1 << CS10)  // set prescaler == 1
    );
}

void init_ADC(void) {
    ADMUX |= (
        (1 << REFS0) |  // set VCC as voltage reference
        (1 << MUX0) | (1 << MUX1) |  // ADC on ADC3 (PORTC3) pin
        (1 << ADLAR)  // adjust ADC result to left
    );

    ADCSRA |= (
        (1 << ADEN) |  // enable ADC
        (1 << ADSC) |  // start ADC conversion
        (1 << ADATE) |  // enable auto trigger
        (1 << ADIE) |  // enable interrupts
        (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2)  // set prescaler == 1024
    );

    DIDR0 |= (1 << ADC3D);  // disable digital input buffer to reduce power consumption (PINC3 will be always 0)
}