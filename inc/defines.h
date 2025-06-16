#include <avr/io.h>

/* modes */
#define WHITE_ON 0
#define YELLOW_ON 1

/* pins */
#define WHITE_LED_PIN PORTB1
#define YELLOW_LED_PIN PORTB2
#define R_BUTTON_PIN PORTD2
#define L_BUTTON_PIN PORTD3

/* limits */
#define ADC_MAX 255
#define PWM_MAX 1023

/* PWM timings */
#define PWM_CHANGE_TIME_MS 3000UL
#define PWM_STEP 1
#define PWM_MIN_CHANGE_DELTA 10


/* button timings */
#define BTN_WAIT_MS 20
#define BTN_DEBOUNCE_CHECK_PERIOD_MS 5
#define BTN_DEBOUNCE_AMOUNT_TO_PASS (BTN_WAIT_MS / BTN_DEBOUNCE_CHECK_PERIOD_MS)

/* TIMER0 */
#define TIMER_BITNESS 8
#define TIMER_SIZE (1 << TIMER_BITNESS)
#define TIMER_PRESCALER_BITNESS 10