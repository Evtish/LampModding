#include "defines.h"
#include <stdint.h>
#include <avr/io.h>

void init_output(volatile uint8_t* ddr_p, const uint8_t pin) {
    *ddr_p |= (1 << pin);  // set led pin as output
}

void init_input(volatile uint8_t* port_p, const uint8_t pin) {
    *port_p |= (1 << pin);  // turn on pull-up resistor
}

// void init_timer0_counter(void) {
//     TCCR0B |= (1 << CS00) | (1 << CS02);  // prescaler == 1024
//     TIMSK0 |= (1 << TOIE0);  // enable overflow interrupt
// }

void init_timer1_PWM(void) {
    TCCR1A |= (
        (1 << COM1A1) |  // non-inverting PWM (OCR1A)
        (1 << COM1B1) |  // non-inverting PWM (OCR1B)
        (0 << WGM10) | (1 << WGM11)  // set 10-bit fast PWM mode
    );

    TCCR1B |= (
        (1 << WGM12) | (1 << WGM13) |  // set 10-bit fast PWM mode
        (0 << CS10) | (1 << CS11) | (0 << CS12)  // set prescaler == 8
    );

    ICR1 = PWM_MAX;

    TIMSK1 |= (1 << TOIE1);  // enable overflow interrupt
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