// #include "typedefs.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    volatile uint8_t* pin_register_p;  // PINx
    uint8_t pin;  // Pxn
    bool was_pressed;
    uint32_t last_call_time;
    uint16_t passed_debounce_amount;
} button_t;

void btn_update(button_t* btn_p);
void btn_poll(button_t* btn_p);
bool btn_is_clicked(button_t* btn_p);