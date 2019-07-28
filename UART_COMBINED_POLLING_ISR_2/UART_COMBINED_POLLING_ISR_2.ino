#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>  

uint8_t temp=0;

#ifndef F_CPU
//define cpu clock speed if not defined
#define F_CPU 16000000UL
#endif

//set desired baud rate
#define BAUDRATE 9600
//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)

void USART_Init()
{
  DDRB=0xff;
  //Set baud rate
  UBRR0L=UBRRVAL;    //low byte
  UBRR0H=(UBRRVAL>>8); //high byte
  //Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = (1<<UCSZ00 | 1<<UCSZ01);
  UCSR0B |=(1<<RXCIE0) | (1<<TXCIE0);
 
  sei();
}

ISR(USART_RX_vect)
{
  PORTB^=1<<1;
  temp=UDR0;
//  UDR0=temp;
}

ISR(USART_TX_vect)
{
  PORTB^=1<<0;
  UDR0=temp;
}

int main(void)
{
  USART_Init();
  while(1)
  {
    
  }
  //nothing here interrupts are working
  return 0;
}
