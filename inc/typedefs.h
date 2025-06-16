#include <stdint.h>
#include <stdbool.h>

typedef struct {
    volatile uint8_t* pin_register_p;  // PINx
    uint8_t pin;  // Pxn
    bool was_pressed;
    uint8_t last_call_time;
    uint16_t passed_debounce_amount;
} button_t;

typedef struct {
    volatile uint16_t* output_p;  // OCRnx
    uint8_t last_call_time;
    bool changing_smoothly;
    uint16_t change_delta_to_use;
} pwm_helper_t;