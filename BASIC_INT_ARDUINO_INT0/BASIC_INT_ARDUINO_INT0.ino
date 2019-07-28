
#include <avr/io.h>
#include <avr/interrupt.h>
//external interrupt 0 = PD2

volatile unsigned int flag=0;
void init()
{
  EICRA = 1<<ISC10 | 1<<ISC11;  // rising edge will create an interrupt request
  EIMSK = (1<<INT0); // external interrupt mask register INT0 is enabled
  //SREG|=(1<<7);      
  sei();         //global interrupt enable
}

int main()
{
  init();
  DDRD &= ~(1<<PD2); //input
  PORTD |= (1<<PD2); // enable pullup resistors
  DDRB |= 0xff;
  
  while(1)
  {
  if(flag==1)
  {
      PORTB ^= 0xff;
      flag=0;
  }
  }
}

ISR(INT0_vect)
{
  flag=1;
  //PORTB ^= 0xff;
}
