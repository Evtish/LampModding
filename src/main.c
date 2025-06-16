#include "defines.h"
#include "inits.h"
#include "button_controls.h"
#include "pwm_controls.h"
#include "timing_controls.h"
#include "utils.h"
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile bool adc_complete = false;

ISR(ADC_vect) {
    adc_complete = true;
}

ISR(TIMER0_OVF_vect) {
    timer0_overflow_amount++;
}

int main(void) {
    uint16_t brightness_level = 0;
    uint8_t light_mode = WHITE_ON;

    pwm_helper_t white_led_pwm = {&OCR1A, 0, false, 0};
    pwm_helper_t yellow_led_pwm = {&OCR1B, 0, false, 0};

    button_t left_btn = {&PIND, L_BUTTON_PIN, false, 0, 0};
    // button_t right_btn = {&PIND, R_BUTTON_PIN, false, 0, 0};

    /* -------------------- GPIO -------------------- */
    init_output(&DDRB, WHITE_LED_PIN);
    init_output(&DDRB, YELLOW_LED_PIN);

    init_input(&PORTD, L_BUTTON_PIN);

    /* -------------------- counter -------------------- */
    init_timer0_counter();

    /* -------------------- PWM -------------------- */
    init_timer1_PWM();

    /* -------------------- ADC -------------------- */
    init_ADC();

    sei();  // allow interrupts;

    while (true) {
        /* -------------------- update ADC value -------------------- */
        if (adc_complete /*&& !white_led_pwm.changing_smoothly && !yellow_led_pwm.changing_smoothly*/) {
            brightness_level = map(ADCH, 0, ADC_MAX, 0, PWM_MAX);  // use 8 high ADC bits only due to the inaccuracy of 1-2 low bits
            adc_complete = false;
        }

        /* -------------------- update button -------------------- */
        btn_poll(&left_btn);

        if (btn_is_clicked(&left_btn)) {
            light_mode = !light_mode;
            white_led_pwm.changing_smoothly = true;
            yellow_led_pwm.changing_smoothly = true;
        }

        /* -------------------- manage light -------------------- */
        switch (light_mode) {
            case WHITE_ON:
                pwm_change(&white_led_pwm, brightness_level);
                pwm_change(&yellow_led_pwm, 0);
                break;
            case YELLOW_ON:
                pwm_change(&yellow_led_pwm, brightness_level);
                pwm_change(&white_led_pwm, 0);
                break;
        }
    }
    
    return 0;
}