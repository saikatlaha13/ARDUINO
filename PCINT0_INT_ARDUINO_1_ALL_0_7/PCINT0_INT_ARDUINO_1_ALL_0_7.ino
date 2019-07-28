#include <avr/io.h>
#include <avr/interrupt.h>

// pcint1 is PB1 pin

volatile unsigned int flag=0;

int main(void)
{  
    DDRB &= ~(1 << PB1 | 1<<PB0 | 1<<PB2 | 1<<PB3 | 1<<PB4 | 1<<PB5);     // Clear the PB0,PB1,PB2,PB3,Pb4 
    PORTB |= (1 << PB1 | 1<<PB0 | 1<<PB2 | 1<<PB3 | 1<<PB4 | 1<<PB5);      // turn On the Pull-up
    DDRD=0xff;                                                    // port D all pins are output
    
    PCICR |= (1 << PCIE0);                                                              // set PCIE0 to enable for PCINCT0 to PCINT7 
    PCMSK0 |= (1 << PCINT1| 1<<PCINT0 | 1<<PCINT2 | 1<<PCINT3 | 1<<PCINT4 | 1<<PCINT5);            // set PCINT1,PCINT0,PCINT3,PCINT4,PCINT5 to trigger an interrupt on state change 

    sei();                                                        // turn on interrupts

    while(1)
    {
      if(flag==1)
      {
        PORTD ^= 0xfc;                                            // toggling port leds
        flag=0;
      }
    }
}

ISR (PCINT0_vect)                                                 // ISR for PCINT0 to PCINT7
{
  flag=1;
  PCIFR &= 1<<0;                                                  // clearing interrupt flag 
}

