#include "utils.h"
#include "timings.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define PWM_MAX 1023

#define PWM_CHANGE_TIME_MS 1000UL  // YOU CAN EDIT THE VALUE (the more the time the longer the animation)
#define PWM_STEP 1  // YOU CAN EDIT THE VALUE (from 1 to PWM_MAX, the less the step the smoother the animation)
#define PWM_MIN_CHANGE_DELTA 10

typedef struct {
    volatile uint8_t* data_direction_r_p;  // DDRx
    volatile uint16_t* out_r_p;  // OCRnx
    uint8_t pin;  // Pxn
    bool changing_smoothly;
    uint32_t last_call_time;
    uint16_t start_change_delta;
} pwm;

// void pwm_assign_and_reset(pwm* pwm_hlpr_p, const uint16_t valid_new_val);
// void pwm_update(pwm* pwm_p, const uint16_t valid_new_val, const uint16_t cur_change_delta);
void pwm_set(pwm* pwm_hlpr_p, const uint16_t new_val);