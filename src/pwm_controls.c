#include "defines.h"
#include "typedefs.h"
#include "timing_controls.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

void pwm_change(pwm_helper_t* pwm_hlpr_p, const uint16_t new_val) {
    const uint16_t valid_new_val = limit(new_val, 0, PWM_MAX);
    const uint16_t cur_change_delta = abs(*(pwm_hlpr_p->output_p) - valid_new_val);
    uint32_t polling_period_ms = 0;

    if (!(pwm_hlpr_p->changing_smoothly)) {
        *(pwm_hlpr_p->output_p) = valid_new_val;
        return;
    }

    if (cur_change_delta < PWM_MIN_CHANGE_DELTA) {
        pwm_hlpr_p->change_delta_to_use = 0;
        pwm_hlpr_p->changing_smoothly = false;
        return;
    }

    if (pwm_hlpr_p->change_delta_to_use == 0) {
        pwm_hlpr_p->change_delta_to_use = cur_change_delta;
    }

    polling_period_ms = PWM_CHANGE_TIME_MS * PWM_STEP / pwm_hlpr_p->change_delta_to_use;

    if (tick_delta(TCNT0, pwm_hlpr_p->last_call_time) >= ms_to_ticks(polling_period_ms)) {
        if (pwm_hlpr_p->change_delta_to_use > PWM_STEP)
            *(pwm_hlpr_p->output_p) += PWM_STEP * (*(pwm_hlpr_p->output_p) < valid_new_val ? 1 : -1);
        else
            *(pwm_hlpr_p->output_p) = valid_new_val;
        
        pwm_hlpr_p->change_delta_to_use *= (*(pwm_hlpr_p->output_p) != valid_new_val);
        pwm_hlpr_p->changing_smoothly = (*(pwm_hlpr_p->output_p) != valid_new_val);
        pwm_hlpr_p->last_call_time = TCNT0;
    }
}