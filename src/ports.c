#include "ports.h"
#include "pic_header.h"

/* ************************************************************************** */

void ports_init(void) {
    // Tri-state control; 0 = output enabled, 1 = output disabled
    // Explicitly disable all outputs
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0xFF;
#ifdef TRISD
    TRISD = 0xFF;
#endif
#ifdef TRISE
    TRISE = 0xFF;
#endif

    // Output latch - explicitly drive all outputs low
    LATA = 0;
    LATB = 0;
    LATC = 0;
#ifdef LATD
    LATD = 0;
#endif
#ifdef LATE
    LATE = 0;
#endif

    // Analog Select; 0 = analog mode is disabled, 1 = analog mode is enabled
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
#ifdef ANSELD
    ANSELD = 0;
#endif
#ifdef ANSELE
    ANSELE = 0;
#endif

    // only on PORTB
    // Weak Pull-up; 0 = pull-up disabled, 1 = pull-up enabled
    WPUB = 0;

    // only on PORTB
    // Interrupt-On-Change; 0 = disabled, 1 = enabled
    IOCB = 0;

    // Slew Rate Control; 0 = maximum slew rate, 1 = limited slew rate
    SLRCON = 0;
}