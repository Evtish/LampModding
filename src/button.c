#include "defines.h"
#include "button.h"
#include "timings.h"
#include <stdint.h>
#include <stdbool.h>

void btn_update(button_t* btn_p) {
    bool btn_is_pressed = !(*(btn_p->pin_register_p) & (1 << btn_p->pin));

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

void btn_poll(button_t* btn_p) {
    uint32_t time_now = get_time_ms();
    if (time_now - btn_p->last_call_time >= BTN_DEBOUNCE_CHECK_PERIOD_MS) {
        btn_p->last_call_time = time_now;
        btn_update(btn_p);
    }
}

bool btn_is_clicked(button_t* btn_p) {
    if (btn_p->passed_debounce_amount >= BTN_DEBOUNCE_AMOUNT_TO_PASS) {
        btn_p->passed_debounce_amount = 0;
        return true;
    }
    return false;
}