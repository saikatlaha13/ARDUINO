#include <avr/io.h>

//10 BIT PWM
int main(void)
{
    //TOP=0X3FF;
    DDRB |= (1 << DDB1)|(1 << DDB2);
    // PB1 and PB2 is now an output

    OCR1A = 0X0000;
    // set PWM 

    TCCR1A =(1 << COM1A0);

   TCCR1A |= 1<<WGM00 | 1<<WGM01;
   TCCR1B |= 1<<WGM13 | 1<<WGM12;
   //FAST PWM OCR1A IS TOP UPDATE AT BOTTOM  
    
    TCCR1B |= (1 << CS10) ;
    // START the timer with no prescaler

    while (1);
    {
        // we have a working Fast PWM
    }
}
