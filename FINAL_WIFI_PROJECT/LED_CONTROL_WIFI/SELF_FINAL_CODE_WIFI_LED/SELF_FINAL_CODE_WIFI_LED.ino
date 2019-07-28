#include <SoftwareSerial.h>
 
#define DEBUG true
#define led_pin 11
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
   
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
//  sendData("AT+CWJAP=\"Redmi\",\"12345678\"\r\n", 5000, DEBUG);//Enter your WiFi network's SSID and Password.
}
 
void loop()
  {
    if (esp8266.available())
      {
        if (esp8266.find("+IPD,"))
          {
            String msg;
            esp8266.find("?");
            msg = esp8266.readStringUntil(' ');
            String command1 = msg.substring(0, 3);
            String command2 = msg.substring(4);
                        
            if (DEBUG) 
              {
                Serial.println(command1);//Must print "led"
                Serial.println(command2);//Must print "ON" or "OFF"
              }
            delay(100);

              if (command2 == "ON") 
                    {
                      digitalWrite(led_pin, HIGH);
                    }
                   else 
                     {
                       digitalWrite(led_pin, LOW);
                     }
          }
      }
  }

 
/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}



