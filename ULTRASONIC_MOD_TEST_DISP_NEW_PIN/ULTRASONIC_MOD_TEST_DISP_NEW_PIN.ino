// pin2 RS
// pin10 enable pin
// A2-4 A3-5 A4-6 A5-7
// R/W to ground

#include <LiquidCrystal.h>
#include<NewPing.h>
 
#define ultrasonicTrigger 11   // trigger pin to 11
#define ultrasonicEcho 12       // echo pin to 12

const int maxDistance = 400;
NewPing ultrasonic(ultrasonicTrigger, ultrasonicEcho, maxDistance);
 
LiquidCrystal lcd(2,10,1,13,A4,A5);
 
float time=0,distance=0;
 
void setup()
{
 lcd.begin(16,2);
 pinMode(ultrasonicTrigger, OUTPUT); 
  pinMode(ultrasonicEcho, INPUT);
 lcd.print(" Ultra sonic");
 lcd.setCursor(0,1);
 lcd.print("Distance Meter");
 delay(2000);
 lcd.clear();
 lcd.print(" Circuit Digest");
 delay(2000);
}
 
void loop()
{
 #if 0
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);
 distance=time*340/20000;
 #endif

 lcd.clear();
 int distance = ultrasonic.ping_cm();
 lcd.clear();
 lcd.print("Distance:");
 lcd.print(distance);
 lcd.print("cm");
 lcd.setCursor(0,1);
 lcd.print("Distance:");
 lcd.print(distance/100);
 lcd.print("m");
 delay(1000);
}

 
