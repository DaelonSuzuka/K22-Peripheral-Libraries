#include "adc.h"
#include "pic_header.h"

/* ************************************************************************** */

void adc_init(void) {
    ADCON1bits.NVCFG = 0; // Negative Voltage Reference, set to Vss
    ADCON1bits.PVCFG = 0; // Positive Voltage Reference, set to VDD

    ADCON2bits.ADFM = 1; // adc result is right-justified

    ADCON0bits.CS = 0; // FOSC, divided by ADCLK
    ADCLK = 0b011111;  // FOSC/64

    ADCON0bits.ADON = 1; // Enable ADC peripheral
}

/* -------------------------------------------------------------------------- */

uint16_t adc_read(uint8_t channel) {
    ADCON0bits.CHS = channel;

    // Engage
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO) {
        // Wait for the conversion to finish
    }

    return ADRES;
}