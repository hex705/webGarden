// garden test #!



#include <Servo.h>


// String buffers for XIG replies
String xigResponse ="";
String serverPrefix = "You said";

// flags for state
boolean abortFlag = false;
boolean markerFlag = false;

boolean response = true;
boolean recovered = true;


boolean valveState;

#define openAngle   70   // angle for released
#define closedAngle 20 // angle for pinched

#define OPEN 70
#define CLOSE 20

#define moisture_input 0
#define divider_top    8
#define divider_bottom 7

#define servoPin 13
#define lightPin A4


int lightLevel;
int moistureLevel;

int waterThreshold = 200; // default
                          // will be zero 

Servo valveServo;

void setup() {
  
 Serial.begin(57600);
 
  // set driver pins to outputs
  pinMode(divider_top,OUTPUT);
  pinMode(divider_bottom,OUTPUT);

  
}

void loop() {
  
  Serial.println("Garden update 2...");
  Serial.println("version 1.0");
  
  int moistureLevel = SoilMoisture();
  int lightLevel = analogRead(lightPin);
  
  String levels = "";
  levels += "moisture ";
  levels += moistureLevel;
  levels += "\t lightlevel ";
  levels += lightLevel;
  
  Serial.println(levels);
  
  if (moistureLevel < waterThreshold) {
    // need to water 
     pinchValve(OPEN);
    // delay(3000);
  }
  
  if (moistureLevel > waterThreshold) {
    // stop watering
      pinchValve(CLOSE);
     // delay(3000);
  }
  
    if ( Serial.available()>0 ) 
  { 
      handleSerial(); 
      xigParse(); 
  }
  
  if ( abortFlag ) xigRecover();
  
  if ( markerFlag  &&  recovered ) xigMarker();

  if ( heartMetro.check()  ) heartBeat();  // let me know the system is alive
  
  if ( updateMetro.check() ) {
  
        if (response) {
            xigUpdate();
          } else {
            lcdMessage("Err: no return");
            abortFlag = true;
          }
        
  }
  
} 

void setWaterThreshold(int t) {
   waterThreshold = t; 
}

void pinchValve(int state) {
   valveServo.attach(servoPin);
   delay(250);
   valveServo.write(state);
   delay(250);
   valveServo.detach();

}

int SoilMoisture(){
   Serial.println("reading moisture");
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
