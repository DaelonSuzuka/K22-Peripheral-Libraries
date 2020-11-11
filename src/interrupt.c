#include "interrupt.h"
#include "pic_header.h"

/* ************************************************************************** */

void begin_critical_section(void) { INTCONbits.GIE = 0; }
void end_critical_section(void) { INTCONbits.GIE = 1; }

/* ************************************************************************** */

void interrupt_init(void) {
    // Clear all peripheral interrupts
    PIE1 = 0x0;
    PIE2 = 0x0;
    PIE3 = 0x0;
    PIE4 = 0x0;
    PIE5 = 0x0;

    INTCONbits.PEIE = 1; // enable peripheral interrupts
    INTCONbits.GIE = 1;  // enable global interrupt
}