/*
Author: Nishan Chettri
Youtube: nishanchettri
Instagram: nishanchettri
email: nishanchettri@gmail.com
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

#define ON_PIN 3
#define WATERING_PIN 4
#define NOT_WATERING_PIN 5

#define soilPin A0
#define relayPin 7
#define STATE_RESET 0
#define STATE_WATERING 1
#define SOIL_THRESHOLD 950

int interval=3;
int state=STATE_RESET;
bool relayState=false;

void setup()
{
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
 pinMode(ON_PIN,OUTPUT);
 pinMode(WATERING_PIN,OUTPUT);
 pinMode(NOT_WATERING_PIN,OUTPUT);
 pinMode(relayPin,OUTPUT);
 
 digitalWrite(ON_PIN,HIGH);
 digitalWrite(WATERING_PIN,LOW);
 digitalWrite(NOT_WATERING_PIN,LOW);

  Serial.begin(9600);
  display.clearDisplay();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40,10);   
  display.println("CODE");
  display.setCursor(35,30);
  display.println("SMART");
  display.setCursor(5,50);
  display.println("IRRIGATION");
  display.display();
  delay(1000);
  display.clearDisplay();
  delay(1000);

}

void loop()
{
  
  float anVal=analogRead(soilPin);
  Serial.println(anVal);
  switch(state)
  {
    case STATE_RESET:
    
    digitalWrite(relayPin,relayState);
    
    if(sensorRead(anVal))
    {
      state=STATE_WATERING;
      relayState=true;
    }
    else
    {
       display.clearDisplay();
       display.setTextSize(2);
       display.setTextColor(WHITE);
       display.setCursor(45,20);   
       display.println("Not");
       display.setCursor(20,40);
       display.println("Watering");
       display.display();
       Serial.println("Not Watering");
       digitalWrite(NOT_WATERING_PIN,LOW);
       state=STATE_RESET;
    }
    break;

    case STATE_WATERING:
    
    for(int i=1;i<interval;i++)
    {
        digitalWrite(relayPin,relayState);
        digitalWrite(WATERING_PIN,relayState);
        Serial.println("watering");
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(20,40);
        display.println("Watering");
        display.display();
        delay(1000);  
    }
    relayState=false;
    state=STATE_RESET;
    break;
     
   
  }
}

bool sensorRead(int val)
{
  int analRead=val;
  if(analRead>SOIL_THRESHOLD)
  return true;

  else
  return false;
}


