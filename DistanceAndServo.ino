#define servo_pin 9
#define TRIG_PIN 6
#define ECHO_PIN 13
#include <Servo.h>
#include <SR04.h>
SR04 sensor = SR04(ECHO_PIN,TRIG_PIN);
Servo myservo;
int angle;
bool updateServo=false;
long a;
void setup() {
  Serial.println("Setup");
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(90);
  angle=0;
}
void loop(){
  a=sensor.DistanceAvg();
  delay(100);
  while(a<30){
    Serial.println("Obstruction detected, attempting to clear.");
    updateServo=true;
    angle=0;
    moveServo();
    a=sensor.DistanceAvg();
    delay(100);
  }
  angle=90;
  if(updateServo){moveServo();updateServo=false;}
}

void moveServo(){
  myservo.write(angle);
}
