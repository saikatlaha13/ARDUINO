
#include <avr/io.h>
#include <avr/interrupt.h>
//external interrupt 0 = PD2

volatile unsigned int flag=0;
void init()
{
  EICRA = 1<<ISC10 | 1<<ISC11;  // rising edge will create an interrupt request
  EIMSK = (1<<INT0 | 1<<INT1); // external interrupt mask register INT0 is enabled
      
  sei();         //global interrupt enable
}

int main()
{
  init();
  DDRD &= ~(1<<PD2 | 1<<PD3); //input
  PORTD |= (1<<PD2 | 1<<PD3); // enable pullup resistors
  DDRB |= 0xff;
  
  while(1)
  {
 
  }
}

ISR(INT0_vect)
{
  PORTB ^= 0x03;
}

ISR(INT1_vect)
{
  PORTB ^= 0x0c;
}


