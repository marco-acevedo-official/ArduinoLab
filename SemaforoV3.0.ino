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
#define WestCross 12
#define WestButton 20

//Global Delay is 1s
#define fast_delay 250
#define blink_delay 250

//This value is multiplied by the global delay
#define green_time 4 
#define yellow_time 2
#define red_time 3
#define cross_time 5
#define cross_blinks 5
#define red_blinks 8

//Keeps Track of the current Cycle and Pedestrian Flags
volatile unsigned int global_state;
volatile unsigned int saved_state;
volatile int FlagN;
volatile int FlagE;
volatile int FlagS;
volatile int FlagW;
volatile unsigned long Delay_time;

const unsigned int blink = 0;
const unsigned int red = 1;
const unsigned int yellow  = 2;
const unsigned int green = 3;
const unsigned int crossing =4;
const unsigned int off =5;

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
}

/*Color changing functions
  0=blink; 1=red; 2=yell; 3=green; 4=ped; 5=off
*/
void SetNorthStoplight(unsigned int color){//TO-DO
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
  if(flagChecker()){
    if((global_state == 2) || (global_state == 5) || (global_state == 8) || (global_state == 11)){//If it's already red do pedestrian and continue
      saved_state = global_state;
      global_state =14;
      delay(2000);
    }
  }

  switch (global_state) {
    case 0:{//EMERGENCY stoplights will blink
      blinkStoplight();
      break;
    }
    case 1:{//All stoplights are turned Red
      allRed();
      delay(Delay_time * red_time);
      break;
    }
    case 2:{//Stoplight N Green
      SetNorthStoplight(3);
      delay(Delay_time * green_time);
      break;
    }
    case 3:{//Stoplight N Yellow
      SetNorthStoplight(2);
      delay(Delay_time * yellow_time);
      break;
    }
    case 4:{//Stoplight N Red
      allRed();
      delay(Delay_time * red_time);
      break;
    }
    case 5:{//Stoplight E Green
      SetEastStoplight(3);
      delay(Delay_time * green_time);
      break;
    }
    case 6:{//Stoplight E Yellow
      SetEastStoplight(2);
      delay(Delay_time * yellow_time);
      break;
    }
    case 7:{//Stoplight E Red
      allRed();
      delay(Delay_time * red_time);
      break;
    }
    case 8:{//S Green
      SetSouthStoplight(3);
      delay(Delay_time * green_time);
      break;
    }
    case 9:{//South Yellow
      SetSouthStoplight(2);
      delay(Delay_time * yellow_time);
      break;
    }
    case 10:{//South Red
      allRed();
      delay(Delay_time * red_time);
      break;
    }
    case 11:{//West Green
      SetWestStoplight(3);
      delay(Delay_time * green_time);
      break;
    }
    case 12:{//West Yellow
      SetWestStoplight(2);
      delay(Delay_time * yellow_time);
      break;
    }
    case 13:{//West Red
      allRed();
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
}

void loop() {
    doByState();
    global_state = global_state + 1;
}
