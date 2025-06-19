// #include "typedefs.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    volatile uint16_t* out_register_p;  // OCRnx
    uint32_t last_call_time;
    bool changing_smoothly;
    uint16_t start_change_delta;
} pwm_t;

void pwm_assign_and_reset(pwm_t* pwm_hlpr_p, const uint16_t valid_new_val);
void pwm_change(pwm_t* pwm_hlpr_p, const uint16_t new_val);