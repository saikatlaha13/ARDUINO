#include <LiquidCrystal.h>

#define BAUDRATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void usart_init();
void usart_send(unsigned char data);
unsigned char usart_receive();
int putstring(char *str);

char string[]="hello world";

int main()
{
  usart_init();
  while(1)
  {
    putstring(string);
    _delay_ms(5000);
  }
  return 0;
}

void usart_init()
{
  UBRR0L |=(uint8_t)(BAUD_PRESCALER>>8);
  UCSR0B |=1<<TXEN0;                        // transmitter enable
  UCSR0B |=1<<RXEN0;                        // receiver enable
  //UCSR0C |=(1<<UCSZ00 | 1<<UCSZ01);         // setting character size to 8 bit 011 setting first and second
  //UCSR0B &= ~(1<<UCSZ02);                   // setting 3rd bit of character size
  UCSR0C=3<<UCSZ00;
}

void usart_send(unsigned char data)
{
  while(!(UCSR0A & 1<<UDRE0));
  UDR0=data; 
}

unsigned char usart_receive()
{
  while(!(UCSR0A & 1<<UDR0));
  return UDR0;
}

int putstring(char *str)
{
  while(*str)
  {
    usart_send(*str);
    str++;
  }
}

