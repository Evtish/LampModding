#include <stdint.h>
#include <stdbool.h>

extern volatile uint32_t timer_overflow_amount_now;

// uint32_t ms_to_ticks(const uint32_t time_ms);
uint32_t ticks_to_ms(const uint32_t ticks);
// uint32_t tick_delta(const uint32_t current_with_overflow, const uint32_t previous_with_overflow);
uint32_t get_time_ms(void);