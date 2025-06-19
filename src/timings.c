#include "defines.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

volatile uint32_t timer_overflow_amount_now = 0;

// uint32_t tick_delta(const uint32_t current_with_overflow, const uint32_t previous_with_overflow) {
//     return current_with_overflow - previous_with_overflow;
// }

// maximum time is 274877906.944ms or 274877.910s or 4581.298min or 76.355h
// uint32_t ms_to_ticks(const uint32_t time_ms) {
//     return (F_CPU / TIMER_PRESCALER_BITNESS) * time_ms / 1000UL;
// }

uint32_t ticks_to_ms(const uint32_t ticks) {
    return ticks * 1000UL / (F_CPU >> TIMER_PRESCALER_BITNESS);
}

uint32_t get_time_ms(void) {
    uint16_t ticks = TCNT1;
    uint32_t overflows = timer_overflow_amount_now;
    // uint32_t ticks_now = TCNT1 + timer_overflow_amount_now * TIMER_SIZE;
    return ticks_to_ms(ticks + overflows * TIMER_SIZE);
}