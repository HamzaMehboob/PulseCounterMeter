/*

  LCD Pulse Counter meter. 
  
  Copyright (c) 2018, hamzamehboob103@gmail.com
  All rights reserved.

  This code is written to be used on Arduino MEga 2560. 

  With described hardware and this firmware it has achieved following functionality till now. 

  * Pulse count sensor input at pin20.
    
  * Buzzer output at 990 pulses and above from pin 8
  
  * Display with 16*2 LCD with LCD(12,11,5,4,3,2) pin configurations. 
   
  * Buzzer can be made off by connecting a button in series with buzzer (hardware changes) 
*/
 
 
 #include <LiquidCrystal.h>
 
LiquidCrystal LCD(12,11,5,4,3,2);
int foundHigh = 1;
int counter = 0;
const byte interruptPin = 20;
const byte buzzerPin = 7;
const byte DisplayPin = 8;
int state = 0; 
int buzzerState = 0;
int pulseConstant = 1000;

void setup() {
   LCD.begin(16,2);
   pinMode(interruptPin, INPUT_PULLUP);
   pinMode(buzzerPin, OUTPUT);
   pinMode(DisplayPin, INPUT);
   attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  handleDisplay();  
  }
  
void loop() {
  if(millis()%500)
  {
      handleDisplay();
      handleBuzzzer();
  }
}

 void blink()
{ 
    if((foundHigh==0) && (digitalRead(interruptPin) == HIGH))
        foundHigh = 1;
    if((foundHigh==1) && (digitalRead(interruptPin) == LOW))
    {
        counter++;
        foundHigh = 0;
    }
 }
 
 void handleBuzzzer()
 {
  if(counter >(pulseConstant-10))
      {
          analogWrite(buzzerPin,buzzerState);
          buzzerState=(buzzerState%40)+5; 
      }
 }
 void handleDisplay()
{
  if(digitalRead(DisplayPin) == LOW)
  {
    state = 0;
   LCD.setCursor(4,0);
   LCD.print("COUNTER");
   LCD.setCursor(6,1);
   LCD.print(counter); 
    }
  else
  {
    state =1;
   LCD.setCursor(4,0);
   LCD.print("CONSTANT");
   LCD.setCursor(6,1);
   LCD.print(pulseConstant); 
    }
    if(state != digitalRead(DisplayPin))
    {
      LCD.clear();
    }
  }
  
  /*
  void setup() {
    pinMode(13,OUTPUT);
    }
    void loop(){
      digitalWrite(13,LOW);
      delay(1000);
      digitalWrite(13,HIGH);
      delay(1000);
      }*/
