 #include <LiquidCrystal.h>
LiquidCrystal LCD(12,11,5,4,3,2);
int foundHigh = 0;
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
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
  handleDisplay();  
  }
  
void loop() {
  if(millis()%500)
  {
      handleDisplay();
  }
}

 void blink()
{ 
  if(digitalRead(interruptPin) == LOW)
    counter++;
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
