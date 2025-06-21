#include "adc.h"

volatile bool adc_complete = false;

//  -------------------------------------------------------------------
// |                       INITIALIZATION STARTS                       |
//  -------------------------------------------------------------------

void adc_init(void) {
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

//  -------------------------------------------------------------------
// |                        INITIALIZATION ENDS                        |
//  -------------------------------------------------------------------