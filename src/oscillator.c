#include "oscillator.h"
#include "pic_header.h"

/* ************************************************************************** */

void internal_oscillator_init(void) {
    OSCCON = 0x70; // SCS FOSC; IRCF 16MHz_HFINTOSC; IDLEN disabled;
    OSCCON2 = 0x04; // PRISD enabled; SOSCGO disabled; MFIOSEL disabled;
    OSCTUNE = 0x40; // INTSRC disabled; PLLEN enabled; TUN 0;
    while (PLLRDY == 0) {
        // Wait for PLL to stabilize
    }
}
