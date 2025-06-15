#include "defines.h"
#include "button_controls.h"

#include <stdint.h>
#include <stdbool.h>

/* update button state */
void btn_update(button* btn_p) {
    bool btn_is_pressed = !PIND_IS_LOW(btn_p->pin);

    if (btn_is_pressed) {
        if (!btn_p->was_pressed)
            btn_p->passed_debounce_amount = 1;
        else if (btn_p->passed_debounce_amount >= 1)
            btn_p->passed_debounce_amount++;
    }
    else
        btn_p->passed_debounce_amount = 0;

    btn_p->was_pressed = btn_is_pressed;
}

void btn_poll(button* btn_p) {
    if (TICK_DELTA(TCNT0, btn_p->last_call_time) >= TIMER_TICK_AMOUNT) {
        btn_update(btn_p);
        btn_p->last_call_time = TCNT0;
    }
}

bool btn_is_clicked(button* btn_p) {
    if (btn_p->passed_debounce_amount >= BTN_DEBOUNCE_AMOUNT_TO_PASS) {
        btn_p->passed_debounce_amount = 0;
        return true;
    }
    return false;
}