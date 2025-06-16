#include <stdint.h>

extern volatile uint32_t timer0_overflow_amount;

uint32_t tick_delta(uint8_t current, uint8_t previous);
uint32_t ms_to_ticks(uint32_t time_ms);