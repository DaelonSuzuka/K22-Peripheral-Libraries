#include "timer.h"
#include "pic_header.h"

/* ************************************************************************** */

/*  Timer0 is used in the UART driver.
    
    Settings:
    Clock Source: FOSC/4
    Prescaler: 1:4
    Secondary Oscillator: disabled
    16-Bit Read/Write Mode: disabled   
    No interrupt
    Do not leave running
    
    T0CON: TIMER0 CONTROL REGISTER
    R/W-1   R/W-1   R/W-1   R/W-1   R/W-1   R/W-1   R/W-1   R/W-1
    TMR0ON  T08BIT  T0CS    T0SE    PSA     T0PS2   T0PS1   T0PS0
    
    bit 7 TMR0ON: Timer0 On/Off Control bit
        1 = Enables Timer0
        0 = Stops Timer0
    bit 6 T08BIT: Timer0 8-Bit/16-Bit Control bit
        1 = Timer0 is configured as an 8-bit timer/counter
        0 = Timer0 is configured as a 16-bit timer/counter
    bit 5 T0CS: Timer0 Clock Source Select bit
        1 = Transition on T0CKI pin
        0 = Internal instruction cycle clock (CLKO)
    bit 4 T0SE: Timer0 Source Edge Select bit
        1 = Increment on high-to-low transition on T0CKI pin
        0 = Increment on low-to-high transition on T0CKI pin
    bit 3 PSA: Timer0 Prescaler Assignment bit
        1 = TImer0 prescaler is not assigned. Timer0 clock input bypasses prescaler.
        0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
    bit 2-0 T0PS<2:0>: Timer0 Prescaler Select bits
        111 = 1:256 Prescale value
        110 = 1:128 Prescale value
        101 = 1:64 Prescale value
        100 = 1:32 Prescale value
        011 = 1:16 Prescale value
        010 = 1:8 Prescale value
        001 = 1:4 Prescale value
        000 = 1:2 Prescale value
*/
uint8_t timer0_clearHigh = 0;
uint8_t timer0_clearLow = 0;

void timer0_init(void)
{
    timer0_stop();
    T0CON = 0b00000111;
    timer0_clear();
}

void timer0_configure(void)
{
    // Empty
}

void timer0_set_clear(uint8_t clearHigh, uint8_t clearLow)
{
    timer0_clearHigh = clearHigh;
    timer0_clearLow = clearLow;
    timer0_clear();
}

void timer0_clear(void)
{
    /*  In 16-bit mode, TMR0H is a buffer register and not the real TMR0H.
        The TMR0H buffer is only written to TMR0H when TMR0L is written.
        
        Therefore, ALWAYS write to TMR0H first, that way we're safe from 
        8-bit/16-bit write problems.
    */
    TIMER0_H_REG = timer0_clearHigh;
    TIMER0_L_REG = timer0_clearLow;
}

void timer0_reset(void)
{
    timer0_stop();
    timer0_clear();
    TIMER0_IF = 0;
}

uint16_t timer0_read(void)
{
    uint16_t retval = 0;
    /*  In 16-bit mode, TMR0H is a buffer register and not the real TMR0H.
        The TMR0H buffer is only read from TMR0H when TMR0L is written.
        
        Therefore, ALWAYS read from TMR0L first, and explicitly. This read
        can be reduced to "retval = (TMR0H << 8) | TMR0L;", but it's safer to
        leave it as two lines to be confident that the L read happens first.
    */
    retval = TIMER0_L_REG;
    retval |= (TIMER0_H_REG << 8);
    return retval;
}

/* ************************************************************************** */

/*  Timer1 is used as stopwatch in the CAT UART driver. It's normally disabled,
    but it's settings will be left until it's needed for something else.

    Settings:
    Clock Source: FOSC/4
    Prescaler 1:4
    Secondary Oscillator: disabled
    16-Bit Read/Write Mode: disabled   
    No interrupt
    Do not leave running
    
    T1CON: TIMER1 CONTROL REGISTER
    R/W-0   R-0     R/W-0   R/W-0   R/W-0   R/W-0   R/W-0   R/W-0
    RD16    T1RUN   T1CKPS1 T1CKPS0 T1OSCEN T1SYNC  TMR1CS  TMR1ON
    
    bit 7 RD16: 16-Bit Read/Write Mode Enable bit
        1 = Enables register read/write of Timer1 in one 16-bit operation
        0 = Enables register read/write of Timer1 in two 8-bit operations
    bit 6 T1RUN: Timer1 System Clock Status bit
        1 = Device clock is derived from Timer1 oscillator
        0 = Device clock is derived from another source
    bit 5-4 T1CKPS<1:0>: Timer1 Input Clock Prescale Select bits
        11 = 1:8 Prescale value
        10 = 1:4 Prescale value
        01 = 1:2 Prescale value
        00 = 1:1 Prescale value
    bit 3 T1OSCEN: Timer1 Oscillator Enable bit
        1 = Timer1 oscillator is enabled
        0 = Timer1 oscillator is shut off
        The oscillator inverter and feedback resistor are turned off to eliminate power drain.
    bit 2 T1SYNC: Timer1 External Clock Input Synchronization Select bit
        When TMR1CS = 1:
        1 = Do not synchronize external clock input
        0 = Synchronize external clock input
        When TMR1CS = 0:
        This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0.
    bit 1 TMR1CS: Timer1 Clock Source Select bit
        1 = External clock from pin RC0/T1OSO/T13CKI (on the rising edge)
        0 = Internal clock (FOSC /4)
    bit 0 TMR1ON: Timer1 On bit
        1 = Enables Timer1
        0 = Stops Timer1
*/

uint8_t timer1_clearHigh = 0;
uint8_t timer1_clearLow = 0;

void timer1_init(void)
{
    timer1_stop();
    T1CON = 0b00110000;
    timer1_clear();
}

void timer1_configure(void)
{
    // Empty
}

void timer1_set_clear(uint8_t clearHigh, uint8_t clearLow)
{
    timer1_clearHigh = clearHigh;
    timer1_clearLow = clearLow;
}

void timer1_clear(void)
{
    /*  In 16-bit mode, TMR1H is a buffer register and not the real TMR1H.
        The TMR1H buffer is only written to TMR1H when TMR1L is written.
        
        Therefore, ALWAYS write to TMR1H first, that way we're safe from 
        8-bit/16-bit write problems.
    */
    TIMER1_H_REG = timer1_clearHigh;
    TIMER1_L_REG = timer1_clearLow;
}

void timer1_reset(void)
{
    timer1_stop();
    timer1_clear();
    TIMER1_IF = 0;
}

uint16_t timer1_read(void)
{
    uint16_t retval;
    /*  In 16-bit mode, TMR1H is a buffer register and not the real TMR1H.
        The TMR1H buffer is only read from TMR1H when TMR1L is written.
        
        Therefore, ALWAYS read from TMR1L first, and explicitly. This read
        can be reduced to "retval = (TMR1H << 8) | TMR1L;", but it's safer to
        leave it as two lines to be confident that the L read happens first.
    */
    retval = TIMER1_L_REG;
    retval |= (TIMER1_H_REG << 8);
    return retval;
}

/* ************************************************************************** */

/*  Timer2 is used for the fast serial bitbang, 115200 baud
        115200 baud = 8.68 us per bit
        32mhz/4 = 8mhz instruction clock
        8mhz instruction clock = 125 ns per instruction
        125 ns x 69 = 8.625 us

    Settings:
    Prescaler = 1:1
    Postscaler = 1:1
    TMR2 Preload = 69
    Actual Interrupt Time = 8.625 us
    No interrupt
    Should be left running

    NOTE: Timer2 should be started during setup and left running.
          Bitbang serial works better with a steady tempo.
          This prevents multiple sequential bytes from bunching and keeps the
          output from being jittery.
          
    T2CON: TIMER2 CONTROL REGISTER
    U-0 R/W-0     R/W-0     R/W-0     R/W-0     R/W-0   R/W-0    R/W-0
    —   T2OUTPS3  T2OUTPS2  T2OUTPS1  T2OUTPS0  TMR2ON  T2CKPS1  T2CKPS0
    
    bit 7 Unimplemented: Read as ‘0’
    bit 6-3 T2OUTPS<3:0>: Timer2 Output Postscale Select bits
        0000 = 1:1 Postscale
        0001 = 1:2 Postscale
        •
        1111 = 1:16 Postscale
    bit 2 TMR2ON: Timer2 On bit
        1 = Timer2 is on
        0 = Timer2 is off
    bit 1-0 T2CKPS<1:0>: Timer2 Clock Prescale Select bits
        00 = Prescaler is 1
        01 = Prescaler is 4
        1x = Prescaler is 16
*/

uint8_t timer2 = 0;

void timer2_init(void)
{
    timer2_stop();
    T2CON = 0b00000000;
    timer2_clear();
}

void timer2_configure(void)
{
    // Empty
}

void timer2_set_clear(uint8_t value)
{
    timer2 = value;
}

void timer2_set_period(uint8_t period)
{
    PR2 = period;
}

void timer2_clear(void)
{
    TIMER2_REG = 0x00;
}

uint8_t timer2_read(void)
{
    return TIMER2_REG;
}

/* ************************************************************************** */

/*  Timer3 is used for the millisecond delay function.
    
    Settings:
    Prescaler = 1:1
    TMR3H = 0xE0
    TMR3L = 0xC0
    No interrupt
    Should not be left running
    
    T3CON: TIMER3 CONTROL REGISTER
    R/W-0 R/W-0   R/W-0    R/W-0    R/W-0   R/W-0   R/W-0   R/W-0
    RD16  T3CCP2  T3CKPS1  T3CKPS0  T3CCP1  T3SYNC  TMR3CS  TMR3ON
    
    bit 7 RD16: 16-Bit Read/Write Mode Enable bit
        1 = Enables register read/write of Timer3 in one 16-bit operation
        0 = Enables register read/write of Timer3 in two 8-bit operations
    bit 6,3 T3CCP<2:1>: Timer3 and Timer1 to CCPx Enable bits
        1x = Timer3 is the capture/compare clock source for the CCP modules
        01 = Timer3 is the capture/compare clock source for CCP2;
        Timer1 is the capture/compare clock source for CCP1
        00 = Timer1 is the capture/compare clock source for the CCP modules
    bit 5-4 T3CKPS<1:0>: Timer3 Input Clock Prescale Select bits
        11 = 1:8 Prescale value
        10 = 1:4 Prescale value
        01 = 1:2 Prescale value
        00 = 1:1 Prescale value
    bit 2 T3SYNC: Timer3 External Clock Input Synchronization Control bit
        (Not usable if the device clock comes from Timer1/Timer3.)
        When TMR3CS = 1:
        1 = Do not synchronize external clock input
        0 = Synchronize external clock input
        When TMR3CS = 0:
        This bit is ignored. Timer3 uses the internal clock when TMR3CS = 0.
    bit 1 TMR3CS: Timer3 Clock Source Select bit
        1 = External clock input from Timer1 oscillator or T13CKI (on the rising edge after the first falling edge)
        0 = Internal clock (F OSC /4)
    bit 0 TMR3ON: Timer3 On bit
        1 = Enables Timer3
        0 = Stops Timer3
*/

uint8_t timer3_clearHigh = 0;
uint8_t timer3_clearLow = 0;

void timer3_init(void)
{
    timer3_stop();
    T3CON = 0b00000000;
    timer3_clear();
}

void timer3_configure(void)
{
    // Empty
}

void timer3_set_clear(uint8_t clearHigh, uint8_t clearLow)
{
    timer3_clearHigh = clearHigh;
    timer3_clearLow = clearLow;
}

void timer3_clear(void)
{
    /*  In 16-bit mode, TMR3H is a buffer register and not the real TMR3H.
        The TMR3H buffer is only written to TMR3H when TMR3L is written.
        
        Therefore, ALWAYS write to TMR3H first, that way we're safe from 
        8-bit/16-bit write problems.
    */
    
    TIMER3_H_REG = timer3_clearHigh;
    TIMER3_L_REG = timer3_clearLow;
}

void timer3_reset(void)
{
    timer3_stop();
    timer3_clear();
    TIMER3_IF = 0;
}

uint16_t timer3_read(void)
{
    uint16_t retval;
    /*  In 16-bit mode, TMR3H is a buffer register and not the real TMR3H.
        The TMR3H buffer is only read from TMR3H when TMR3L is written.
        
        Therefore, ALWAYS read from TMR3L first, and explicitly. This read
        can be reduced to "retval = (TMR3H << 8) | TMR3L;", but it's safer to
        leave it as two lines to be confident that the L read happens first.
    */
    retval = TIMER3_L_REG;
    retval |= (TIMER3_H_REG << 8);
    return retval;
}