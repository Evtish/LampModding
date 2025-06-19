#include "defines.h"
#include "pwm.h"
#include "timings.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

void pwm_assign_and_reset(pwm_t* pwm_p, const uint16_t valid_new_val) {
    *(pwm_p->out_register_p) = valid_new_val;
    pwm_p->start_change_delta = 0;
    pwm_p->changing_smoothly = false;
}

void pwm_change(pwm_t* pwm_p, const uint16_t new_val) {
    const uint16_t valid_new_val = limit(new_val, 0, PWM_MAX);
    const uint16_t cur_change_delta = abs(*(pwm_p->out_register_p) - valid_new_val);

    if (pwm_p->start_change_delta == 0) {
        pwm_p->start_change_delta = cur_change_delta;
    }

    if (!(pwm_p->changing_smoothly) || pwm_p->start_change_delta < PWM_MIN_CHANGE_DELTA) {
        pwm_assign_and_reset(pwm_p, valid_new_val);
        return;
    }

    const uint32_t polling_period_ms = PWM_CHANGE_TIME_MS * PWM_STEP / pwm_p->start_change_delta;
    uint32_t time_now = get_time_ms();
    if (time_now - pwm_p->last_call_time >= polling_period_ms) {
        pwm_p->last_call_time = time_now;

        if (cur_change_delta > PWM_STEP)
            *(pwm_p->out_register_p) += PWM_STEP * (*(pwm_p->out_register_p) < valid_new_val ? 1 : -1);
        else {
            pwm_assign_and_reset(pwm_p, valid_new_val);
            return;
        }
    }
}