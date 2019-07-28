//---------------------------------------------------
/*CSilva 2014
ADC using using direct port access and 
Interrupt based sampling
Manual settings for ADC clock and Resolution/*
Results  stored in an array and easily accessible by the main loop
Array bits printed on serial port
AN0;AN1.AN2,AN3,AN4,AN5*/
//---------------------------------------------------

int i=0;
//Set how many analogue inputs to read, starting from A0
const int ADC_CHANNELS = 6;
//Create a N position array to store the result of the ADC conversions
int myvar[ADC_CHANNELS];
unsigned int flag=0;

void setup()
{
  Serial.begin(9600);      //begin Serial comm
  
  ADMUX |= (1 << REFS0);     // Set ADC reference to AVCC
  ADMUX |= (1 << ADLAR);     // Left Adjust the result 
  ADCSRA |= (1 << ADEN);     // Enable ADC
  ADCSRA |= (1 << ADIE);     // Enable ADC Interrupt
  sei();                     // Enable Global Interrupts
  ADCSRA |= (1 << ADSC);     // Start A2D Conversions  */
}

void loop()
{
  Serial.print(" 0 ");
  Serial.print(myvar[0]);
  Serial.print(" 1 ");
  Serial.print(myvar[1]);
  Serial.print(" 2 ");
  Serial.print(myvar[2]);
  Serial.print(" 3 ");
  Serial.print(myvar[3]);
  Serial.print(" 4 ");
  Serial.print(myvar[4]);
  Serial.print(" 5 ");
  Serial.println(myvar[5]);
 
  delay(500);
}
//******************************************************
//-------------------ADC interrupt----------------------
//When the conversion is complete, increment the counter 
//to read the next channel and update the variables
//******************************************************

ISR(ADC_vect)           
{
  
  if(flag==0)
  {
    myvar[0]=ADCH;
  }
  if(flag==1)
  {
    myvar[1]=ADCH;
  }
  if(flag==2)
  {
    myvar[2]=ADCH;
  }
  if(flag==3)
  {
    myvar[3]=ADCH;
  }
  if(flag==4)
  {
    myvar[4]=ADCH;
  }
  if(flag==5)
  {
    myvar[5]=ADCH;
  }
 //Count up to n channels
 //(myvar[i]) = ADCH;
 
  if (++i >= ADC_CHANNELS)
  {
    i=0;
  } 

  ADMUX = (1<<ADLAR) | (1<<REFS0) | i; //Select ADC Channel
  ADCSRA |= (1 << ADSC);    // Start A2D Conversions
  flag=i; 
} 
