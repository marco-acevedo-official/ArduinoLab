/****************************************************/
/* Laboratoy No 2 4 way trafic stoplight with pedestrian Light*/
/*  Marco Antonio Acevedo Gonzalez    */
/****************************************************/  

//Stoplight Pin number definitions
#define NorthRed 8
#define NorthYellow 7
#define NorthGreen 6
#define NorthCross 5
#define NorthButton 2

#define EastRed 22
#define EastYellow 23
#define EastGreen 24
#define EastCross 25
#define EastButton 3

#define SouthRed 26
#define SouthYellow 27
#define SouthGreen 28
#define SouthCross 29
#define SouthButton 21

#define WestRed 11
#define WestYellow 10
#define WestGreen 9
#define WestCross 53
#define WestButton 20

//Global Delay is 1s
#define fast_delay 250
#define blink_delay 250

//This value is multiplied by the global delay
#define green_time 15 
#define yellow_time 5
#define red_time 5
#define cross_time 5
#define cross_blinks 5
#define red_blinks 8

#define latchPin 12 // RCLK
#define clockPin 13 // SRCLK
#define dataPin 45 //ser dataPin

#define displayZ 40
#define displayY 41
#define displayX 42
#define displayW 43
///////////////////////////////////////////////////////
//Keeps Track of the current Cycle and Pedestrian Flags
volatile unsigned int global_state;//Keeps track of which part of the cycle the stoplight is at
volatile unsigned int saved_state;//Saved the state before switching to the pedetrian function
volatile int FlagN; //Used to determine if the pedestrian is waiting
volatile int FlagE; //Used to determine if the pedestrian is waiting
volatile int FlagS; //Used to determine if the pedestrian is waiting
volatile int FlagW; //Used to determine if the pedestrian is waiting
volatile unsigned long Delay_time;//Is reduced when a pedestrian is waiting

//State definitions for logic control.
const unsigned int blink = 0;
const unsigned int red = 1;
const unsigned int yellow  = 2;
const unsigned int green = 3;
const unsigned int crossing =4;
const unsigned int off =5;

unsigned long display_time; //How long will a 7seg stay light for?
unsigned long currTime; //For use with millis
unsigned long prevDisplayTime; //For use with millis
unsigned long stoplightTime;//For use with millis
unsigned long lightTime;//How long will the color of the stoplight remain lit for
int showTime =0;

//Library definitions to convert alpha-numerical to 7seg byte
byte seven_seg_digits[31] = {
  B11111100, // = 0
  B01100000, // = 1
  B11011010, // = 2
  B11110010, // = 3
  B01100110, // = 4
  B10110110, // = 5
  B10111110, // = 6
  B11100000, // = 7
  B11111110, // = 8
  B11100110, // = 9
  B11101110, // = A
  B00111110, // = b
  B10011100, // = C
  B00011010, // = c
  B01111010, // = d
  B10011110, // = E
  B10001110, // = F
  B01101110, // = H
  B00101110, // = h
  B01110000, // = J
  B00011100, // = L
  B00101010, // = n
  B00111010, // = o
  B11001110, // = P
  B10001100, // = r
  B10110110, // = S
  B01111100, // = U
  B00111000, // = u
  B00010010, // = =
  B00000010,  // = -
  B01110110   //y
  };

byte displayData[4]={B00000000,B00000000,B00000000,B00000000};//Hold the complete string of chars to output to 7seg
//String letters;
char characters[5];
int currentSegment =0;
int i = 0;

void setup() {
 
  //Enabling Each Pin As IO
  pinMode(NorthCross, OUTPUT);
  pinMode(NorthRed,OUTPUT);
  pinMode(NorthYellow, OUTPUT);
  pinMode(NorthGreen, OUTPUT);
  pinMode(NorthButton, INPUT_PULLUP);

  pinMode(EastCross, OUTPUT);
  pinMode(EastRed,OUTPUT);
  pinMode(EastYellow, OUTPUT);
  pinMode(EastGreen, OUTPUT);
  pinMode(EastButton, INPUT_PULLUP);

  pinMode(SouthCross, OUTPUT);
  pinMode(SouthRed,OUTPUT);
  pinMode(SouthYellow, OUTPUT);
  pinMode(SouthGreen, OUTPUT);
  pinMode(SouthButton, INPUT_PULLUP);

  pinMode(WestCross, OUTPUT);
  pinMode(WestRed,OUTPUT);
  pinMode(WestYellow, OUTPUT);
  pinMode(WestGreen, OUTPUT);
  pinMode(WestButton, INPUT_PULLUP);

  //For the 4 x 7seg display
  pinMode(displayW, OUTPUT);
  pinMode(displayX, OUTPUT);
  pinMode(displayY, OUTPUT);
  pinMode(displayZ, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

 //Define the Pin to ISR
  attachInterrupt(digitalPinToInterrupt(NorthButton),SetFlagN,CHANGE); //Attached the Interrupt subroutine
  attachInterrupt(digitalPinToInterrupt(EastButton),SetFlagE,CHANGE); //Attached the Interrupt subroutine
  attachInterrupt(digitalPinToInterrupt(SouthButton),SetFlagS,CHANGE); //Attached the Interrupt subroutine
  attachInterrupt(digitalPinToInterrupt(WestButton),SetFlagW,CHANGE); //Attached the Interrupt subroutine

  Serial.begin(9600); //Used for debugging

 //Assigning Initial Value to variables
  Delay_time = 1000;
  FlagN=0;
  FlagE=0;
  FlagS=0;
  FlagW=0;
  global_state = 0;
  saved_state = 0;

  currTime=millis();
  display_time=10;
  currentSegment =1;
}

/*Color changing functions
  0=blink; 1=red; 2=yell; 3=green; 4=ped; 5=off
*/
void SetNorthStoplight(unsigned int color){
  switch(color){
    case 0:{//blink red
      blinkStoplight();
      break;
    }

      case 1:{//Red
        digitalWrite (NorthGreen,LOW);
        digitalWrite (NorthYellow,LOW);
        digitalWrite (NorthCross,LOW);
        digitalWrite (NorthRed,HIGH);
      break;
      }

      case 2:{//Yellow
        digitalWrite (NorthGreen,LOW);
        digitalWrite (NorthCross,LOW);
        digitalWrite (NorthRed,LOW);
        digitalWrite (NorthYellow,HIGH);
      break;
      }

      case 3:{//Green
        digitalWrite (NorthYellow,LOW);
        digitalWrite (NorthCross,LOW);
        digitalWrite (NorthRed,LOW);
        digitalWrite (NorthGreen,HIGH);
      break;
      }

      case 4:{//Pedestrian Crossing
        digitalWrite (NorthGreen,LOW);
        digitalWrite (NorthYellow,LOW);
        digitalWrite (NorthRed,HIGH);
        //TO-DO FUNCTION FOR PEDESTRIAN ALGORITHM
      break;
      }

      case 5:{// Turn off LED
        digitalWrite (NorthGreen,LOW);
        digitalWrite (NorthYellow,LOW);
        digitalWrite (NorthRed,LOW);
        digitalWrite (NorthCross,LOW);
        break;
      }

      default:{
        global_state=0;
        blinkStoplight();
      }
  }
}

void SetEastStoplight(unsigned int color){

  switch(color){
    case 0:{//blink red
      blinkStoplight();
      break;
    }

      case 1:{//Red
        digitalWrite (EastGreen,LOW);
        digitalWrite (EastYellow,LOW);
        digitalWrite (EastCross,LOW);
        digitalWrite (EastRed,HIGH);
      break;
    }

      case 2:{//Yellow
        digitalWrite (EastGreen,LOW);
        digitalWrite (EastCross,LOW);
        digitalWrite (EastRed,LOW);
        digitalWrite (EastYellow,HIGH);
      break;
    }

      case 3:{//Green
        digitalWrite (EastYellow,LOW);
        digitalWrite (EastCross,LOW);
        digitalWrite (EastRed,LOW);
        digitalWrite (EastGreen,HIGH);
      break;
    }

      case 4:{//Pedestrian Crossing
        digitalWrite (EastGreen,LOW);
        digitalWrite (EastYellow,LOW);
        digitalWrite (EastRed,HIGH);
        //TO-DO FUNCTION FOR PEDESTRIAN ALGORITHM
      break;
    }


      case 5:{// Turn off LED
        digitalWrite (EastGreen,LOW);
        digitalWrite (EastYellow,LOW);
        digitalWrite (EastRed,LOW);
        digitalWrite (EastCross,LOW);
        break;
      }

      default:{
        global_state=0;
        blinkStoplight();
      }

  }

}

void SetSouthStoplight(unsigned int color){

  switch(color){
    case 0:{//blink red
      blinkStoplight();
      break;
    }

      case 1:{//Red
        digitalWrite (SouthGreen,LOW);
        digitalWrite (SouthYellow,LOW);
        digitalWrite (SouthCross,LOW);
        digitalWrite (SouthRed,HIGH);
      break;
    }

      case 2:{//Yellow
        digitalWrite (SouthGreen,LOW);
        digitalWrite (SouthCross,LOW);
        digitalWrite (SouthRed,LOW);
        digitalWrite (SouthYellow,HIGH);
      break;
    }

      case 3:{//Green
        digitalWrite (SouthYellow,LOW);
        digitalWrite (SouthCross,LOW);
        digitalWrite (SouthRed,LOW);
        digitalWrite (SouthGreen,HIGH);
      break;
    }

      case 4:{//Pedestrian Crossing
        digitalWrite (SouthGreen,LOW);
        digitalWrite (SouthYellow,LOW);
        digitalWrite (SouthRed,HIGH);
        //TO-DO FUNCTION FOR PEDESTRIAN ALGORITHM
      break;
    }
      case 5:{// Turn off LED
        digitalWrite (SouthGreen,LOW);
        digitalWrite (SouthYellow,LOW);
        digitalWrite (SouthRed,LOW);
        digitalWrite (SouthCross,LOW);
        break;
      }
      default:{
        global_state=0;
        blinkStoplight();
      }
  }

}

void SetWestStoplight(unsigned int color){

  switch(color){
    case 0:{//blink red
      blinkStoplight();
      break;
    }

    case 1:{//Red
        digitalWrite (WestGreen,LOW);
        digitalWrite (WestYellow,LOW);
        digitalWrite (WestCross,LOW);
        digitalWrite (WestRed,HIGH);
      break;
    }

    case 2:{//Yellow
        digitalWrite (WestGreen,LOW);
        digitalWrite (WestCross,LOW);
        digitalWrite (WestRed,LOW);
        digitalWrite (WestYellow,HIGH);
      break;
    }

    case 3:{//Green
        digitalWrite (WestYellow,LOW);
        digitalWrite (WestCross,LOW);
        digitalWrite (WestRed,LOW);
        digitalWrite (WestGreen,HIGH);
      break;
    }

    case 4:{//Pedestrian Crossing
        digitalWrite (WestGreen,LOW);
        digitalWrite (WestYellow,LOW);
        digitalWrite (WestRed,HIGH);
        //TO-DO FUNCTION FOR PEDESTRIAN ALGORITHM
      break;
    }
    case 5:{//LED Off
        digitalWrite (WestGreen,LOW);
        digitalWrite (WestYellow,LOW);
        digitalWrite (WestCross,LOW);
        digitalWrite (WestRed,LOW);
      break;
    }

    default:{
        global_state=0;
        blinkStoplight();
    }

  }


}

/* Set Flags ISR */
void SetFlagN(void){// Pedestrian in N is waiting
  FlagN=1;
  Delay_time = 500;
    Serial.println("INTERRUPT N");
}

void SetFlagE(void){// Pedestrian in E is waiting, CASE 9
  FlagE=1;
  Delay_time = 500;
  Serial.println("INTERRUPT E");
}

void SetFlagS(void){// Pedestrian in S is waiting, CASE 9
  FlagS=1;
  Delay_time = 500;
  Serial.println("INTERRUPT S");
}

void SetFlagW(void){// Pedestrian in W is waiting, CASE 9
  FlagW=1;
  Delay_time = 500;
  Serial.println("INTERRUPT W");
}

/*Pedestrian Turn Functions
  once called they will set all stoplights red
  and iluminate the corresponding LED
*/
void NorthPed(){
      allRed();
      Delay_time = 1000;
      //Turn on cross light and hold
      digitalWrite(NorthCross,HIGH);
      delay(Delay_time*cross_time);

      //Start blinking the crossing light to warn time is over
      for(i=0;i<cross_blinks;i++){
        digitalWrite(NorthCross,LOW);
        delay(250);
        digitalWrite(NorthCross,HIGH);
        delay(250);
      }

      //Turn off pedestrian crossing light
      digitalWrite(NorthCross,LOW);
      FlagN = 0;
}

void EastPed(){
      allRed();
      Delay_time = 1000;
      //Turn on cross light and hold
      digitalWrite(EastCross,HIGH);
      delay(Delay_time*cross_time);

      //Start blinking the crossing light to warn time is over
      for(i=0;i<cross_blinks;i++){
        digitalWrite(EastCross,LOW);
        delay(250);
        digitalWrite(EastCross,HIGH);
        delay(250);
      }

      //Turn off pedestrian crossing light
      digitalWrite(EastCross,LOW);
      FlagE=0;
}

void SouthPed(){

      allRed();
      Delay_time = 1000;
      //Turn on cross light and hold
      digitalWrite(SouthCross,HIGH);
      delay(Delay_time*cross_time);

      //Start blinking the crossing light to warn time is over
      for(i=0;i<cross_blinks;i++){
        digitalWrite(SouthCross,LOW);
        delay(250);
        digitalWrite(SouthCross,HIGH);
        delay(250);
      }

      //Turn off pedestrian crossing light
      digitalWrite(SouthCross,LOW);
      FlagS=0;

}

void WestPed(){

      allRed();
      Delay_time = 1000;
      //Turn on cross light and hold
      digitalWrite(WestCross,HIGH);
      delay(Delay_time*cross_time);

      //Start blinking the crossing light to warn time is over
      for(i=0;i<cross_blinks;i++){
        digitalWrite(WestCross,LOW);
        delay(250);
        digitalWrite(WestCross,HIGH);
        delay(250);
      }

      //Turn off pedestrian crossing light
      digitalWrite(WestCross,LOW);
      FlagW=0;

}
//////////////////////////////////////////////

/* Makes all stoplights blink
   Takes over for red_blinks * (2*blink_delay)
*/
void blinkStoplight(){
  //delays are ok here since the 7 seg will not be showing usefull data
  for(i=0;i<red_blinks;i++){
    allRed();
    delay(blink_delay);
    allOff();
    delay(blink_delay);
  }
}

void allOff(){
  SetNorthStoplight(5);
  SetEastStoplight(5);
  SetSouthStoplight(5);
  SetWestStoplight(5);
}

//All stoplights are set to Red
void allRed(){
  SetNorthStoplight(1);
  SetEastStoplight(1);
  SetSouthStoplight(1);
  SetWestStoplight(1);
}

bool flagChecker(){
  return ((numberOfFlags())>0);
}

int numberOfFlags(){
  return (FlagN + FlagS + FlagE + FlagW);
}

//Cycle function / Decision making
void doByState(){// Desiscion making function. Decides what to do based on the global_state variable

  if(flagChecker()){//What to do when a pedestrian flag is detected
    if((global_state == 2) || (global_state == 5) || (global_state == 8) || (global_state == 11)){//If it's already red do pedestrian and continue. These numbers show the next state, not the current state
      saved_state = global_state;
      global_state =14;//This will make the switch statement jump to the pedestrian routine
      delay(2000);
    }//else if the light is still not red continue the regular cycle until it is red
  }
  unsigned long elapsed = currTime - stoplightTime;
  showTime = (lightTime - elapsed)/1000;
  deleteDisplayData();
  stringToDisplay(String(showTime));
  if(elapsed >= lightTime){//elapsed = currTime - stoplightTime. 
  switch (global_state) {
    case 0:{//EMERGENCY stoplights will blink
      blinkStoplight();
      break;
    }

    case 1:{//All stoplights are turned Red
      allRed();
      lightTime = red_time * Delay_time;
      stoplightTime=currTime;
      //delay(Delay_time * red_time);
      break;
    }

    case 2:{//Stoplight N Green
      SetNorthStoplight(3);
      //delay(Delay_time * green_time);
      lightTime = Delay_time * green_time;
      stoplightTime=currTime;
      break;
    }

    case 3:{//Stoplight N Yellow
      SetNorthStoplight(2);
      //delay(Delay_time * yellow_time);
      lightTime = Delay_time * yellow_time;
      stoplightTime=currTime;
      break;
    }

    case 4:{//Stoplight N Red
      allRed();
      //delay(Delay_time * red_time);
      lightTime = red_time * Delay_time;
      stoplightTime=currTime;
      break;
    }

    case 5:{//Stoplight E Green
      SetEastStoplight(3);
      //delay(Delay_time * green_time);
            lightTime = Delay_time * green_time;
      stoplightTime=currTime;
      break;
    }

    case 6:{//Stoplight E Yellow
      SetEastStoplight(2);
      //delay(Delay_time * yellow_time);
            lightTime = Delay_time * yellow_time;
      stoplightTime=currTime;
      break;
    }

    case 7:{//Stoplight E Red
      allRed();
      //delay(Delay_time * red_time);
            lightTime = red_time * Delay_time;
      stoplightTime=currTime;
      break;
    }

    case 8:{//S Green
      SetSouthStoplight(3);
      //delay(Delay_time * green_time);
      lightTime = Delay_time * green_time;
      stoplightTime=currTime;
      break;
    }

    case 9:{//South Yellow
      SetSouthStoplight(2);
      //delay(Delay_time * yellow_time);
      lightTime = Delay_time * yellow_time;
      stoplightTime=currTime;
      break;
    }

    case 10:{//South Red
      allRed();
      //delay(Delay_time * red_time);
      lightTime = red_time * Delay_time;
      stoplightTime=currTime;
      break;
    }

    case 11:{//West Green
      SetWestStoplight(3);
      //delay(Delay_time * green_time);
      lightTime = Delay_time * green_time;
      stoplightTime=currTime;
      break;
    }

    case 12:{//West Yellow
      SetWestStoplight(2);
      //delay(Delay_time * yellow_time);
      lightTime = Delay_time * yellow_time;
      stoplightTime=currTime;
      break;
    }

    case 13:{//West Red
      allRed();
      lightTime = red_time * Delay_time;
      stoplightTime=currTime;
      global_state=1;
      break;
    }

    case 14:{//flag is set
      if(FlagN==1){NorthPed();}
      if(FlagE==1){EastPed();}
      if(FlagS==1){SouthPed();}
      if(FlagW==1){WestPed();}
      delay(2000);
      global_state = saved_state-1;
      break;
    }
  //-----------------------------------------------------------------------
     default:{//This should never happen, but if it does it turns on blinkers
      global_state = -1;
     }
    }//end Switch
       global_state = global_state + 1;
}//end if millis
}

// display a number on the digital segment display
void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  //shiftOut(dataPin,clockPin,LSBFIRST,array position)
  shiftOut(dataPin, clockPin, LSBFIRST, digit);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}

byte sevenSegChar(char c){
  switch(c){
    case '0':{
      return seven_seg_digits[0];
    }

    case '1':{
      return seven_seg_digits[1];
    }

    case '2':{
      return seven_seg_digits[2];
    }

    case '3':{
      return seven_seg_digits[3];
    }

    case '4':{
      return seven_seg_digits[4];
    }

    case '5':{
      return seven_seg_digits[5];
    }

    case '6':{
      return seven_seg_digits[6];
    }

    case '7':{
      return seven_seg_digits[7];
    }

    case '8':{
      return seven_seg_digits[8];
    }

    case '9':{
      return seven_seg_digits[9];
    }

    case 'A':{
      return seven_seg_digits[10];
    }

    case 'b':{
      return seven_seg_digits[11];
    }

    case 'C':{
      return seven_seg_digits[12];
    }

    case 'c':{
      return seven_seg_digits[13];
    }

    case 'd':{
      return seven_seg_digits[14];
    }

    case 'E':{
      return seven_seg_digits[15];
    }

    case 'F':{
      return seven_seg_digits[16];
    }

    case 'H':{
      return seven_seg_digits[17];
    }

    case 'h':{
      return seven_seg_digits[18];
    }

    case 'J':{
      return seven_seg_digits[19];
    }

    case 'L':{
      return seven_seg_digits[20];
    }

    case 'n':{
      return seven_seg_digits[21];
    }

    case 'o':{
      return seven_seg_digits[22];
    }

    case 'P':{
      return seven_seg_digits[23];
    }

    case 'r':{
      return seven_seg_digits[24];
    }

    case 'S':{
      return seven_seg_digits[25];
    }

    case 'U':{
      return seven_seg_digits[26];
    }

    case 'u':{
      return seven_seg_digits[27];
    }

    case '=':{
      return seven_seg_digits[28];
    }

    case '-':{
      return seven_seg_digits[29];
    }

    case 'y':{
      return seven_seg_digits[29];
    }

    case 'z':{
      return seven_seg_digits[2];
    }

    case 'Z':{
      return seven_seg_digits[2];
    }

    default:{
      return B00000000;
    }
  }
}

void displayEnable(int j){
  switch(j){
    case 1:{
      digitalWrite(displayW,LOW);
      digitalWrite(displayX,HIGH);
      digitalWrite(displayY,HIGH);
      digitalWrite(displayZ,HIGH);
      break;
    }
    case 2:{
      digitalWrite(displayW,HIGH);
      digitalWrite(displayX,LOW);
      digitalWrite(displayY,HIGH);
      digitalWrite(displayZ,HIGH);
      break;
    }
    case 3:{
      digitalWrite(displayW,HIGH);
      digitalWrite(displayX,HIGH);
      digitalWrite(displayY,LOW);
      digitalWrite(displayZ,HIGH);
      break;
    }
    case 4:{
      digitalWrite(displayW,HIGH);
      digitalWrite(displayX,HIGH);
      digitalWrite(displayY,HIGH);
      digitalWrite(displayZ,LOW);
      break;
    }
  }
}

void stringToDisplay(String input){
  int position = input.length()-1;
  if(position>3){position=3;}//overflow avoidance
  for(i=position;i>=0;i--){
    characters[i] = input[i];
    displayData[i]=sevenSegChar(characters[i]);
  }
}

void deleteDisplayData(){
  for(i=0;i<4;i++){
    displayData[i]=B00000000;
  }
}

void loop() {
  currTime = millis();

  if(currTime - prevDisplayTime >= display_time){//7 segment x 4 display process scheduler. Changes the active display when elapsed time is at or above the expected time
    if(currentSegment==5){currentSegment=1;}
    sevenSegWrite(displayData[currentSegment-1]);
    displayEnable(currentSegment);
    currentSegment = (currentSegment +1);
    prevDisplayTime=currTime;
  }

   doByState();//after writing to the display execute the stoplight funciton
}



