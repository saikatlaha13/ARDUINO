
// ICP1 IS AT PB0
void timer1_init();

int main()
{
  DDRB=1<<5;
  timer1_init();
  for(;;)
  {
  }
} 

void timer1_init()
{ 
  TCCR1B = (1<<CS11 | 1<<CS10);          // clk/64
  TIMSK1 |= (1 << ICIE1) ;                   // UNMASK ICIE1  
  TCCR1A |= 1<<WGM11 | 1<<WGM10;                   
   sei();  
}

ISR(TIMER1_CAPT_vect)
{
  PORTB ^= 1<<5;
}
