#define sys_clock 16000000UL
#define baudrate (((sys_clock / (9600 * 16UL))) - 1) 
char *ptr="123456789";
char *str=ptr;
unsigned int mil;
unsigned int count=900;

int main()
{
  DDRB=0xff;
  USART_init();
  sei();
 
  while(1)
  {
    UDR0=*str++;
    if(!(*str))
    {
      str=ptr;
    }
  }
}

void USART_init()
{
  UBRR0L  = (uint8_t)(baudrate);
  UBRR0H  = (uint8_t)(baudrate>>8);
  UCSR0B |= (1<<RXCIE0) | (1<<TXCIE0); //RX AND TX complete interrupt enable 0
  UCSR0B |= (1<<RXEN0 | 1<<TXEN0);     // receiver and transmitter enable 0
  UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); // CHARACTER SIZE IS OF 8 BITS
}

ISR(USART_RX_vect)
{
  //PORTB|=1;
   ++mil;
  if(mil==count)
  {
   PORTB^=0x03;
   mil=0;
  }
}

ISR(USART_UDRE_vect)
{
  PORTB|=1<<1;
}

ISR(USART_TX_vect)
{
  ++mil;
  if(mil==count)
  {
   PORTB^=0x03;
   mil=0;
  }
}



