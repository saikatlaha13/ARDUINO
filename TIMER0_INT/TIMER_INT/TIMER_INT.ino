#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_init(void);            //Function prototype

volatile unsigned long milis = 0;   //This is our shared volatile variable that will be used as the milis count

int main(void){

   DDRB = (1<<PB5);           //Set the pin as an output
   timer0_init();

   for(;;){
      if(milis >= 500){
         PORTB ^= (1<<PB5);//Toggle the led at every 500ms/0.5s/2hz
         milis=0;
      }
   }
   return 0;
}

void timer0_init(void){

   TCCR0A = (1<<WGM01);           //Timer in CTC mode
   TCCR0B = ((1<<CS01)|(1<<CS00));  //1:64 prescaler
   OCR0A = 249;                 //Value to have an compare at every 1ms
   TIMSK0 = (1<<OCIE0A);          //Enable timer interrupts
   sei();                     //Enable global interrupts
}

ISR(TIMER0_COMPA_vect){

   milis++;    //Increase milis count by one millisecond
}

