#ifndef _TIMER_H_
#define _TIMER_H_

/* ************************************************************************** */

/*  These #define's are provided as a comprimise between the desire for
    appropriate layers of abstraction and the real-world constraints of 
    embedded projects.
    
    Function calls take up more code space, take more CPU cycles, and reduce
    clarity in timing-critical situations. On the other hand, touching registers
    from 'userspace' is gross.
*/

#define TIMER0_IF INTCONbits.TMR0IF
#define TIMER1_IF PIR1bits.TMR1IF
#define TIMER2_IF PIR1bits.TMR2IF
#define TIMER3_IF PIR2bits.TMR3IF

#define TIMER0_ON T0CONbits.TMR0ON
#define TIMER1_ON T1CONbits.TMR1ON
#define TIMER2_ON T2CONbits.TMR2ON
#define TIMER3_ON T3CONbits.TMR3ON

#define TIMER0_H_REG TMR0H
#define TIMER0_L_REG TMR0L
#define TIMER1_H_REG TMR1H
#define TIMER1_L_REG TMR1L
#define TIMER2_REG TMR2
#define TIMER3_H_REG TMR3H
#define TIMER3_L_REG TMR3L

/* ************************************************************************** */

/*  Timer usage directory:
    
    Timer0 is used in the UART driver.
    Timer1 is not used
    Timer2 is used in bitbang serial communication.  Free-running.
    Timer3 is used for the millisecond delay function.  Not free-running.
*/

/* ************************************************************************** */

/*  Setup and control function for hardware timers.
    Each timerX_init() and timerX_clear() can be customized for desired timer duration.

    timerX_init(void)
        Initializes timerX with minimum, safe default values.
        DOES NOT start timerX
        
    timer0_configure(void)
        Not currently implemented: Will eventually allow userspace control of
        TXCON and other registers.
        
    timerX_set_clear(uint8_t clearHigh, uint8_t clearLow)
        Allows the user to set the values that will be used to clear the timer.
        Clear values will default to 0 if not set by the user.
        
    timerX_set_period(uint8_t period)
        Sets the Period Register, for timers that have one.
    
    timerX_start(void)
        Starts the timer.
    
    timerX_stop(void)
        Stops the timer.
    
    timerX_clear(void)
        Sets the TMRXH and TMRXL registers to the configured clearHigh/Low
        from timerX_set()
    
    timerX_reset(void)
        Stops the timer, clears it's count, and clears it's Interrupt Flag.
        DOES NOT restart timer.
    
    timerX_read(void)
        Returns the value of the timerX count register(s). Return type is an
        uintX_T that matches the width of the timer.
*/

/* -------------------------------------------------------------------------- */

// Timer0 setup functions
extern void timer0_init(void);
extern void timer0_configure(void);
extern void timer0_set_clear(uint8_t clearHigh, uint8_t clearLow);
// Timer0 control functions
#define timer0_start(); TIMER0_ON = 1;
#define timer0_stop(); TIMER0_ON = 0;
#define timer0_IF_clear() TIMER0_IF = 0
#define timer0_IF_read() TIMER0_IF
extern void timer0_clear(void);
extern void timer0_reset(void);
extern uint16_t timer0_read(void);

/* -------------------------------------------------------------------------- */

// Timer1 setup functions
extern void timer1_init(void);
extern void timer1_configure(void);
extern void timer1_set_clear(uint8_t clearHigh, uint8_t clearLow);
// Timer1 control functions
#define timer1_start(); TIMER1_ON = 1;
#define timer1_stop(); TIMER1_ON = 0;
extern void timer1_clear(void);
extern void timer1_reset(void);
extern uint16_t timer1_read(void);

/* -------------------------------------------------------------------------- */

// Timer2 setup functions
extern void timer2_init(void);
extern void timer2_configure(void);
extern void timer2_set_clear(uint8_t clear);
extern void timer2_set_period(uint8_t period);
// Timer2 control functions
#define timer2_start(); TIMER2_ON = 1;
#define timer2_stop(); TIMER2_ON = 0;
extern void timer2_clear(void);
extern void timer2_reset(void);
extern uint8_t timer2_read(void);

/* -------------------------------------------------------------------------- */

// Timer3 setup functions
extern void timer3_init(void);
extern void timer3_configure(void);
extern void timer3_set_clear(uint8_t clearHigh, uint8_t clearLow);
// Timer3 control functions
#define timer3_start(); TIMER3_ON = 1;
#define timer3_stop(); TIMER3_ON = 0;
extern void timer3_clear(void);
extern void timer3_reset(void);
extern uint16_t timer3_read(void);


#endif
