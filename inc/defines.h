#include <avr/io.h>

/* modes */
#define WHITE_ON 0
#define YELLOW_ON 1

/* pins */
#define WHITE_LED_PIN PORTB1
#define YELLOW_LED_PIN PORTB2
#define R_BUTTON_PIN PORTD2
#define L_BUTTON_PIN PORTD3

/* button timings */
#define BTN_WAIT_MS 20
#define BTN_DEBOUNCE_CHECK_PERIOD_MS 5
#define BTN_DEBOUNCE_AMOUNT_TO_PASS (BTN_WAIT_MS / BTN_DEBOUNCE_CHECK_PERIOD_MS)

/* TIMER0 */
#define TIMER_BITNESS 8
#define TIMER_SIZE (1 << TIMER_BITNESS)
#define TIMER_PRESCALER ((1 << CS00) | (1 << CS02))  // 1024
#define TIMER_PRESCALER_PWR_INDX 10
#define TIMER_TICK_AMOUNT ((F_CPU >> TIMER_PRESCALER_PWR_INDX) * BTN_DEBOUNCE_CHECK_PERIOD_MS / 1000 - 1)

/* with parameters */
#define PIND_IS_LOW(x) (PIND & (1 << (x)))
#define TICK_DELTA(counter, val) ((counter) >= (val) ? (counter) - (val) : TIMER_SIZE + (counter) - (val))