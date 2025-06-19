/* modes */
#define WHITE_ON 0
#define YELLOW_ON 1

/* pins */
#define WHITE_LED_PIN PORTB1
#define YELLOW_LED_PIN PORTB2
#define R_BUTTON_PIN PORTD2
#define L_BUTTON_PIN PORTD3

/* limits */
#define ADC_MAX 255  // use ADCH only
#define PWM_MAX 1023

/* TIMER1 */
#define TIMER_SIZE PWM_MAX
#define TIMER_PRESCALER_BITNESS 3

/* PWM timings */
#define PWM_CHANGE_TIME_MS 2000UL
#define PWM_STEP 1
#define PWM_MIN_CHANGE_DELTA 10

/* button timings */
#define BTN_WAIT_MS 1000UL
#define BTN_DEBOUNCE_CHECK_PERIOD_MS 5
#define BTN_DEBOUNCE_AMOUNT_TO_PASS (BTN_WAIT_MS / BTN_DEBOUNCE_CHECK_PERIOD_MS)