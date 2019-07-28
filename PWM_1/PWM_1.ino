#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void){
  
  unsigned char i=0;

  DDRD = (1<<PD6);  //Set our pwm pin as an output
  
  //Timer configuration
  TCCR0A = ((1<<COM0A1)|(1<<WGM01)|(1<<WGM00)); //Enable pwm mode in pin PD6 and set the WGM bits to Fast pwm mode
  TCCR0B = ((1<<CS01)|(1<<CS00));     //Set prescaler to 64 


  for(;;){
    
    //Fade up
    for(i=0; i<255;i++){
      OCR0A = i;  //Set new duty cycle value
      _delay_ms(50);  //delay a litle bit
    }

    //Fade down
    for(i=255; i>0;i--){
      OCR0A = i;  //Set new duty cycle value
      _delay_ms(25);  //delay a litle bit
    }
  }

  return 0;
}

