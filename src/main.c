#include "modes.h"
#include "gpio.h"
#include "button.h"
#include "timings.h"
#include "pwm.h"
#include "adc.h"
#include "utils.h"
#include <avr/interrupt.h>

ISR(ADC_vect) {
    adc_complete = true;
}

ISR(TIMER1_OVF_vect) {
    timer_overflow_amount_now++;
}

int main(void) {
    light_mode led_light_mode = WHITE_ON;
    uint16_t brightness_level = 0;

    pwm white_led_pwm = {&DDRB, &OCR1A, WHITE_LED_PIN};
    pwm yellow_led_pwm = {&DDRB, &OCR1B, YELLOW_LED_PIN};

    button left_button = {&PORTD, &PIND, LEFT_BUTTON_PIN};
    // button right_button = {&PORTD, &PIND, RIGHT_BUTTON_PIN};

    //  -------------------------------------------------------------------
    // |                       INITIALIZATION STARTS                       |
    //  -------------------------------------------------------------------

    /* --------------- GPIO --------------- */
    gpio_output_init(white_led_pwm.data_direction_r_p, white_led_pwm.pin);
    gpio_output_init(yellow_led_pwm.data_direction_r_p, yellow_led_pwm.pin);
    // gpio_output_init(&DDRB, PB5);

    gpio_input_init(left_button.port_r_p, left_button.pin);
    // gpio_input_init(right_button.port_r_p, right_button.pin);

    /* --------------- counter & PWM --------------- */
    timer1_init();
    sei();  // allow interrupts;

    /* --------------- ADC --------------- */
    adc_init();

    //  -------------------------------------------------------------------
    // |                        INITIALIZATION ENDS                        |
    //  -------------------------------------------------------------------

    while (true) {
        /* --------------- update ADC value --------------- */
        if (adc_complete) {
            brightness_level = map(ADCH, 0, ADC_MAX, 0, PWM_MAX);  // use 8 high ADC bits only due to the inaccuracy of 1-2 low bits
            adc_complete = false;
        }

        /* --------------- update button --------------- */
        // button_poll(&right_button);

        // if (button_is_clicked(&right_button)) PORTB ^= (1 << PB5);

        button_poll(&left_button);

        if (button_is_clicked(&left_button) /*&& !white_led_pwm.changing_smoothly && !yellow_led_pwm.changing_smoothly*/) {
            led_light_mode = (led_light_mode == WHITE_ON) ? YELLOW_ON : WHITE_ON;
            white_led_pwm.changing_smoothly = true;
            yellow_led_pwm.changing_smoothly = true;
        }

        /* --------------- manage light --------------- */
        switch (led_light_mode) {
            case WHITE_ON:
                pwm_set(&white_led_pwm, brightness_level);
                pwm_set(&yellow_led_pwm, 0);
                break;
            case YELLOW_ON:
                pwm_set(&yellow_led_pwm, brightness_level);
                pwm_set(&white_led_pwm, 0);
                break;
        }
    }
    
    return 0;
}