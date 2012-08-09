#include <Narcoleptic.h>

// garden test #!



#include <Servo.h>


#include <LiquidCrystal.h> 
#include <Metro.h> // http://www.arduino.cc/playground/Code/Metro  (link checked Jan, 2012)
//#include "Characters.h"


Metro updateMetro = Metro(20000L);

int idleCount;


// String buffers for XIG replies
String xigResponse =  "" ;
String serverPrefix = "You said: ";

// flags for state
boolean abortFlag = false;
boolean markerFlag = false;

boolean response = true;
boolean recovered = true;

boolean valveState;


#define WATERING 60
#define STOP_WATERING 15

#define OPEN 1
#define CLOSED 0

int waterThreshold = 20; // default - 200

#define moisture_input 0
#define divider_top    8
#define divider_bottom 7

#define servoPin 12
#define lightPin A4


int lightLevel;
int moistureLevel;


                          // will be zero 

Servo valveServo;

void setup() {
  
 Serial.begin(57600);
 valveServo.attach(servoPin);
 
  // set driver pins to outputs
  pinMode(divider_top,OUTPUT);
  pinMode(divider_bottom,OUTPUT);
  
  
 
  pinchValve(STOP_WATERING);
  valveState=CLOSED;
 
   pinMode(13,OUTPUT);
   pinMode(11,OUTPUT);
    xigUpdate();
}

void loop() {
  
 digitalWrite(11,HIGH);
 delay(100);
 digitalWrite(11,LOW);
 delay(100);
 // problem is we can't see what is going on inside 
 
  // Serial.println("Garden update 2...");
  // Serial.println("version 1.0");
 
   moistureLevel = SoilMoisture();
   lightLevel = analogRead(lightPin);
            
  String levels = "";
  levels += "moisture ";
  levels += moistureLevel;
  levels += "\t lightlevel ";
  levels += lightLevel;
  
 // Serial.println(levels);
  
  if (moistureLevel < waterThreshold) {
    // need to water 
     pinchValve(WATERING);
     valveState = OPEN;
    // delay(3000);
  }
  
  if (moistureLevel > waterThreshold) {
    // stop watering
      pinchValve(STOP_WATERING);
      valveState=CLOSED;
     // delay(3000);
  }
  
    if ( Serial.available()>0 ) 
  { 
      handleSerial(); 
      xigParse(); 
  }
  
  if ( abortFlag ) xigRecover();
  
  if ( markerFlag  &&  recovered ) xigMarker();
  
  if ( updateMetro.check() ) {
  
        if (response) {
             
            moistureLevel = SoilMoisture();
            lightLevel = analogRead(lightPin);
            xigUpdate();
            
          } else {
          //  lcdMessage("Err: no return");
            abortFlag = true;
          }
        
  }
  
} 

void setWaterThreshold(int t) {
   waterThreshold = t; 
}

void pinchValve(int state) {
   
   valveServo.write(state);

}

int SoilMoisture(){
  //Serial.println("reading moisture");
  
  int reading;
 
  // drive a current through the divider in one direction
  digitalWrite(divider_top,HIGH);
  digitalWrite(divider_bottom,LOW);

  // wait a moment for capacitance effects to settle
  delay(1000);

  // take a reading
  reading=analogRead(moisture_input);

  // reverse the current
  digitalWrite(divider_top,LOW);
  digitalWrite(divider_bottom,HIGH);

  // give as much time in 'revers'e as in 'forward'
  delay(1000);

  // stop the current
  digitalWrite(divider_bottom,LOW);

  return reading;

}
