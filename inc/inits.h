#include <stdint.h>

void init_output(volatile uint8_t* ddrx_p, const uint8_t pin);
void init_input(volatile uint8_t* portx_p, const uint8_t pin);
void init_timer0_counter(void);
void init_timer1_PWM(void);
void init_ADC(void);