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
   TCCR1B=(1<<CS11 | 1<<CS10);                   // clk/64
   TIMSK1 |= (1 << TOIE1);           // enable timer overflow interrupt 
   sei();  
}

ISR(TIMER1_OVF_vect)
{ 
  PORTB ^= 1<<5;
}

