//covering the ir sensor gives a low output
//*------ Arduino Line Follower Code----- */
// header file for ultrasonic sensor
#include <NewPing.h>

/*-------definning Inputs------*/
#define LS 2       // left sensor
#define RS 3       // right sensor

/*-------definning Outputs------*/
#define LM1 4      // left motor
#define LM2 5      // left motor
#define RM1 6      // right motor
#define RM2 7      // right motor

#define LME 8      // right motor enable for pwm
#define RME 9      // left motor enable for pwm

#define ultrasonicTrigger 11
#define ultrasonicEcho 12
#define maxDistance 400
#define MIN_DISTANCE_FROM_OBJECT 5

NewPing ultrasonic(ultrasonicTrigger, ultrasonicEcho, maxDistance);

void setup()
{
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  pinMode(ultrasonicTrigger, OUTPUT); 
  pinMode(ultrasonicEcho, INPUT);
}

void loop()
{
  if(digitalRead(LS) && digitalRead(RS))     // Move Forward
  {
    move_forward();
  }
  
  if(!(digitalRead(LS)) && digitalRead(RS))     // Turn right
  {
    move_right();
  }
  
  if(digitalRead(LS) && !(digitalRead(RS)) )     // turn left
  {
    move_left();
  }
  
  if(!(digitalRead(LS)) && !(digitalRead(RS)) )     // stop
  {
    stop_moving();
  }

  if((obstacle_detection())==1)     // stop
  {
    stop_moving();
    
    while(obstacle_detection())
    {
      delay(100);
    }

    diversion();
  }
}

void move_forward()
{
   digitalWrite(LM1, HIGH);
   digitalWrite(LM2, LOW);
   digitalWrite(RM1, HIGH);
   digitalWrite(RM2, LOW);
   return;
}

void move_left()
{
   digitalWrite(LM1, HIGH);
   digitalWrite(LM2, LOW);
   digitalWrite(RM1, LOW);
   digitalWrite(RM2, LOW);
   return;
}

void move_right()
{
   digitalWrite(LM1, LOW);
   digitalWrite(LM2, LOW);
   digitalWrite(RM1, HIGH);
   digitalWrite(RM2, LOW);
   return;
}

void stop_moving()
{
   digitalWrite(LM1, LOW);
   digitalWrite(LM2, LOW);
   digitalWrite(RM1, LOW);
   digitalWrite(RM2, LOW);
   return;
}

int obstacle_detection()
{
  int distance = ultrasonic.ping_cm();
  return ((distance > 0) && (distance <= MIN_DISTANCE_FROM_OBJECT));
}

void diversion()
{
  unsigned int i;

  delay(2000);
  move_back();
  delay(2000);
  for(i=0 ; i<40000 ; i++)  //turn right
  {
    move_right();
  }
  delay(2000);
  for(i=0 ; i<40000 ; i++) //turn left
  {
    move_left();
  }
  delay(2000);

  return;
}

void move_back()
{
  unsigned int i;

  for(i=0 ; i<5 ; i++)
  {
   digitalWrite(LM1, LOW);
   digitalWrite(LM2, HIGH);
   digitalWrite(RM1, LOW);
   digitalWrite(RM2, HIGH);
  }
   return;
}


