#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#define ADC_MAX 255  // use ADCH only

extern volatile bool adc_complete;

void adc_init(void);