//#include "stm32f103xb.h"

 #define segment1 1<<0;
 #define segment2 1<<1;
 #define segment3 1<<2;
 #define segment4 1<<3;
 
 void display(unsigned int i);
 void view(unsigned int );
 unsigned int b[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
 
 int main(void)
 {
 volatile uint32_t dly;
   
    unsigned int i,j;     
   // unsigned int a[10]={0x003F,0x0006,0x005B,0x004F,0x0066,0x006D,0x007D,0x0007,0x007F,0x006F};
    //unsigned int b[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPCEN;
   
    GPIOA->CRL = 0x22222222;
    GPIOB->CRL = 0x22222222;
    GPIOB->CRH = 0x22222222;
      
    while (1) 
    {
      for(i=0 ; i<10000 ; i++)
      {
        for(j=0 ; j<20 ; j++)
        {
        display(i);
        }
      }
   }
 }
 
 void display(unsigned int num)
 {
   unsigned int m;
   unsigned int ones,tens,hundred,thousand;
   
   ones= num % 10;
   num = num / 10;
   
   tens= num % 10;
   num = num /10;
   
   hundred=num%10;
   num = num/10;
  
   thousand=num%10;
  
   GPIOC->ODR=segment1;
   view(ones);
   for(m=0 ; m<10000 ; m++);
   
   GPIOC->ODR=segment2;
   view(tens);
   for(m=0 ; m<10000 ; m++);
   
   GPIOC->ODR=segment3;
   view(hundred);
   for(m=0 ; m<10000 ; m++);
   
   GPIOC->ODR=segment4;
   view(thousand);
   for(m=0 ; m<10000 ; m++);
 }
 
 void view(unsigned int i)
 {
   volatile uint32_t k;
   GPIOB->ODR=b[i]<<3;
   for(k=0 ; k<10000 ; k++);
 }
   
   
   
   
   
   
   
   
   
   
   
 //=============================================================================
 // End of file
 //=============================================================================

