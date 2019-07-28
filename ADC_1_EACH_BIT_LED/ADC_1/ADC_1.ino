#include <avr/io.h>

int adc_value;         //Variable used to store the value read from the ADC converter
unsigned int b[16]={ 0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
 

int main(void){

DDRB|=0xff;
DDRD|=0xff;
//DDRD |= (1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6);     //PB5/digital 13 is an output

ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));     //Prescaler at 128 so we have an 125Khz clock source
ADMUX &= (~(1<<MUX3) | ~(1<<MUX2) | ~(1<<MUX1) | ~MUX0); // selecting channel 0
ADMUX |= (1<<REFS0);                              // reference 0th bit
ADMUX &= ~(1<<REFS1);                             //Avcc(+5v) as voltage reference  reference 1st bit
ADMUX &= (~(1<<MUX3) | ~(1<<MUX2) | ~(1<<MUX1) | ~MUX0); // selecting channel 0
ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));    //ADC in free-running mode      // trigger selection
ADCSRA &= ~(1<<ADATE);                             //Signal source, in this case is the free-running  //enable auto trigger
ADCSRA |= (1<<ADEN);                              //Power up the ADC  //enable adc
ADCSRA |= (1<<ADSC);                              //Start converting  

  for(;;){            //The infinite loop
    
    adc_value = ADCW;//Read the ADC value, really that's just it
      PORTB |= (adc_value & 1)|(adc_value & 1<<1)|(adc_value & 1<<2)|(adc_value & 1<<3)|(adc_value & 1<<4) | (adc_value & 1<<5);
      PORTD |= (adc_value & 1<<6) | (adc_value & 1<<7);
     // _delay_ms(300); 
//      ADCSRA |= (1<<ADSC); 
      PORTB=PORTD=0x00;
      //_delay_ms(300);


    /*ADMUX &= (~(1<<MUX3) | ~(1<<MUX2) | ~(1<<MUX1) | MUX0); // selecting channel 0
      ADCSRA |= (1<<ADSC);  
       PORTB |= (adc_value & 1)|(adc_value & 1<<1)|(adc_value & 1<<2)|(adc_value & 1<<3)|(adc_value & 1<<4) | (adc_value & 1<<5);
      PORTD |= (adc_value & 1<<6) | (adc_value & 1<<7);
      ADCSRA |= (1<<ADSC);*/  

  }

return 0;
}

