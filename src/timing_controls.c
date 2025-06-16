#include "defines.h"
#include <stdint.h>

// TODO: fix that timer0_overflow_amount is used by everything. if must be separated. or use 16-bit timer1
volatile uint32_t timer0_overflow_amount = 0;

uint32_t tick_delta(uint8_t current, uint8_t previous) {
    uint32_t overflowed_part = TIMER_SIZE * timer0_overflow_amount;
    timer0_overflow_amount = 0;

    return overflowed_part + ((current - previous) & 0xFF);  // "& 0xFF" is removing '-' from a number
}

// maximum time is 274877906.944ms or 274877.910s or 4581.298min or 76.355h
uint32_t ms_to_ticks(uint32_t time_ms) {
    return (F_CPU >> TIMER_PRESCALER_BITNESS) * time_ms / 1000;
}