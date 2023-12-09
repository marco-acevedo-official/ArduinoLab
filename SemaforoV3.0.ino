/****************************************************/
/* Laboratoy No 2 trafic light with pedestrian Light*/
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
#define Delay_time 1000

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

const unsigned int blink = 0;
const unsigned int red = 1;
const unsigned int yellow  = 2;
const unsigned int green = 3;
const unsigned int crossing =4;
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
  FlagN=0;
  FlagE=0;
  FlagS=0;
  FlagW=0;
  global_state = 0;
  saved_state = 0;
}

void SetNorthStoplight(unsigned int color){//TO-DO
  switch(color){
    case 0:{//blink red
      //TO-DO FUNCTION FOR ALL BLINKING
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
  }
}

void SetEastStoplight(unsigned int color){

  switch(color){
    case 0:{//blink red
      //TO-DO FUNCTION FOR ALL BLINKING
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
  }

}

void SetSouthStoplight(unsigned int color){

  switch(color){
    case 0:{//blink red
      //TO-DO FUNCTION FOR ALL BLINKING
      break;
    }

      case 1:{//Red
        digitalWrite (SouthGreen,LOW);
        digitalWrite (NorthYellow,LOW);
        digitalWrite (NorthCross,LOW);
        digitalWrite (NorthRed,HIGH);
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
  }

}

void SetWestStoplight(unsigned int color){

  switch(color){
    case 0:{//blink red
      //TO-DO FUNCTION FOR ALL BLINKING
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
        digitalWrite (EWestRed,LOW);
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
  }


}

void doByState(){// Desiscion making function. Decides what to do based on the global_state variable
   switch (global_state) {
    case 0:{//EMERGENCY stoplights will blink
      for(i=0;i<red_blinks;i++){
        //allOff();//TO-DO: No such function
        delay(250);
        allRed();
        delay(250);
      }
      break;
    }
    case 1:{//All stoplights are turned Red
      allRed();
      delay(Delay_time * red_time);
      break;
    }
    case 2:{//Stoplight A Green
      SetNorthStoplight(2);
      delay(Delay_time * green_time);
        break;
    }
    case 3:{//Stoplight A Yellow
      SetNorthStoplight(3);
      delay(Delay_time * yellow_time);
      break;
    }
    case 4:{//Stoplight A Red
      allRed();
      delay(Delay_time * red_time);
      break;
    }
    case 5:{//Stoplight B Green
      stBsetGreen();
      delay(Delay_time * green_time);
      break;
    }
    case 6:{//Stoplight B Yellow
      stBsetYellow();
      delay(Delay_time * yellow_time);
      break;
    }
    case 7:{//Flag checker. If no Pedestrian Flags are set, the global state is reset so the cycle can begin
            //Handles next actions based on the number and Flag that is set
      if((FlagA + FlagB) > 0){ //A Pedestrian is Waiting
         allRed(); // Turns RED all stoplights to prepare traffic for pedestrians
         delay(Delay_time * red_time);// Holds the stoplight RED to clear the road
         if((FlagA + FlagB) == 2){//2 pedestrians waiting
          break;
         }else{//Only 1 pedestrian waiting
               if(FlagA == 1){
                  break;
               }else{
                     global_state++;
                     break;
                }
         }//Only 1 pedestrian waiting else end
      }else{//No pedestrian waiting. This else is for the first If statement
        global_state = 0;
      }
      break;
    }// End bracket for Case 7
    case 8:{//Pedestrian A Waiting
      if(FlagA ==0){break;}//Skips this routine of there are no Pedestrian A waiting
     
      FlagA = 0;

      PedAroutine();
     
      //Checks to see if pedestrian B is also waiting
      if(FlagB == 1){break;}
      else{global_state = 0;}
      break;
    }

    case 9:{//Pedestrian B Waiting
      FlagB = 0;

      PedBroutine();

      global_state = 0;
      break;
    }
  //-----------------------------------------------------------------------
     default:{//This should never happen, but if it does it turns on blinkers
      FlagA = 0;
      FlagB = 0;
      global_state = -1;
     };
    }//end Switch
}

void SetFlagN(void){// Pedestrian in N is waiting
  FlagN=1;
    Serial.println("INTERRUPT N");
}

void SetFlagE(void){// Pedestrian in E is waiting, CASE 9
  FlagE=1;
  Serial.println("INTERRUPT E");
}

void SetFlagS(void){// Pedestrian in S is waiting, CASE 9
  FlagS=1;
  Serial.println("INTERRUPT S");
}

void SetFlagW(void){// Pedestrian in W is waiting, CASE 9
  FlagW=1;
  Serial.println("INTERRUPT W");
}

void allRed(){//TO-DO: All stoplights are set to Red
  SetNorthStoplight(1);
  SetEastStoplight(1);
  SetSouthStoplight(1);
  SetWestStoplight(1);
}

void NorthPed(){
      allRed();
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
}

void EastPed(){
      allRed();
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
}

void SouthPed(){

      allRed();
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

}

void WestPed(){

      allRed();
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

}
   
void loop() {
    doByState();
    global_state = global_state + 1;
}




