/************************
motor using
the L293D chip
************************/
#include <LiquidCrystal.h>
#define ENABLE 5
#define DIRA 3 //Right - Clockwise
#define DIRB 4
unsigned long currTime=0;
unsigned long prevTimeSpeedUp=0;
unsigned long updateTime=10000;
int i=-1;
int speed=0;
bool enable=false;
bool updateLCD=true;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Booting");
  lcd.clear();
}

//true or false
void enableMotor(bool e){
  if(e){
    analogWrite(ENABLE,speed);
    Serial.print("Motor Enabled: speed = ");Serial.println(speed);
  }else{
    digitalWrite(ENABLE,LOW);
  }
}

//0-255
void setSpeed(int s){
  updateLCD=true;
  if(s>255){
    speed=255;
  }
  if(s<0){
    speed=0;
  }
  if(s>-1 && s<256){
    speed=s;
  }  
}

//'r' or 'l'
void setDir(char d){
  if(d =='r'){
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
    Serial.println("Motor Clockwise: ");
  }else{
    if(d == 'l'){
    digitalWrite(DIRA,LOW); //one way
    digitalWrite(DIRB,HIGH);
    Serial.println("Motor Counter Clockwise: ");
    }
  }
}

void loop() {
  if(updateLCD){
    lcd.clear();
    lcd.print("Motor Speed ");
    
    lcd.print(int((speed/255.0)*100.0));lcd.print("%");
    updateLCD=false;
  }

  currTime = millis();

  //SpeedUp
  if(currTime-prevTimeSpeedUp>updateTime){
    speedUp(10.0);
  }

  //Serial available
  if((Serial.available())>(0)){
    //Wait for data
    String inputString = Serial.readString();
    inputString.trim();
    //Parse command: Turn On, Turn Off, Motor CW, Motor CC
    Serial.print("Received String ");Serial.println(inputString);
    processString(inputString);
  }

}
   
void speedUp(float p){
    speed=speed+percentToInt(p);
    setSpeed(speed);
    prevTimeSpeedUp = millis();
}

int percentToInt(float p){
   return int((p/100.0)*255.0);
}

void processString(String inputString) {
  if (inputString.equalsIgnoreCase("Turn On")) {
    // Code for Option1
    enableMotor(true);
  } else if (inputString.equalsIgnoreCase("Turn Off")) {
    // Code for Option2
    enableMotor(false);
  } else if (inputString.equalsIgnoreCase("Motor CW")) {
    // Code for Option3
    setDir('r');
  } else if (inputString.equalsIgnoreCase("Motor CC")) {
    // Code for Option4
    setDir('l');
  } else {
    // Default case or error handling
    Serial.println("Invalid option. Please choose Option1, Option2, Option3, or Option4.");
  }
}
