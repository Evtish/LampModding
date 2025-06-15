#include "defines.h"
#include "inits.h"
#include "button_controls.h"
#include "utils.h"

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile bool adc_complete = false;

ISR(ADC_vect) {
    adc_complete = true;
}

int main(void) {
    uint16_t brightness_level = 0;
    uint8_t light_mode = WHITE_ON;

    button left_btn = {L_BUTTON_PIN, false, 0, 0};
    button right_btn = {R_BUTTON_PIN, false, 0, 0};

    /* -------------------- GPIO -------------------- */
    init_output(&DDRB, WHITE_LED_PIN);
    init_output(&DDRB, YELLOW_LED_PIN);

    init_input(&PORTD, L_BUTTON_PIN);
    init_input(&PORTD, R_BUTTON_PIN);

    /* -------------------- button timer -------------------- */
    init_timer0_counter();

    /* -------------------- PWM -------------------- */
    init_timer1_PWM();

    /* -------------------- ADC -------------------- */
    init_ADC();

    sei();  // allow interrupts;

    while (true) {
        /* -------------------- update ADC value -------------------- */
        if (adc_complete) {
            brightness_level = map(ADCH, 0, 255, 0, 1023);  // use 8 high ADC bits only due to the inaccuracy of 1-2 low bits
            adc_complete = false;
        }

        /* -------------------- update buttons -------------------- */
        btn_poll(&left_btn);
        btn_poll(&right_btn);

        if (btn_is_clicked(&left_btn)) light_mode = WHITE_ON;
        if (btn_is_clicked(&right_btn)) light_mode = YELLOW_ON;

        /* -------------------- manage light -------------------- */
        switch (light_mode) {
            case WHITE_ON:
                OCR1A = brightness_level;
                OCR1B = 0;
                break;
            case YELLOW_ON:
                OCR1B = brightness_level;
                OCR1A = 0;
                break;
        }
    }
    
    return 0;
}