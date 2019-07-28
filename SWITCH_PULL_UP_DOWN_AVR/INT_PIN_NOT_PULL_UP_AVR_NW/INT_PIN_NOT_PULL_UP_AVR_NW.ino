int main()
{
  DDRB = ~(1<<PB0);    // making PB0 pin as an input pin
  PORTB = ~PB0;       // configuring PB0 in pull up mode
  PORTB = 1<<PB1;      // making pin PB1 as the output pin

  while(1)
  {
    PORTB = ~(1<<PB1);   // normally the led is off
    if((PINB & 1)==1)    // switch on
    {
      PORTB = 1<<1;
    }
    if((PINB & 1)==0)       // switch off
    {
      PORTB = 0x00;
    }
  }
}
 

