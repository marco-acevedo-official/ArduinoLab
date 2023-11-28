/****************************************************/
/* Laboratoy No 2 trafic light with pedestrian Light*/
/*  Marco Antonio Acevedo Gonzalez    */
/****************************************************/  
 
//Stoplight A Pin number definitions
#define stA_red 12
#define stA_yellow 11
#define stA_green 10
#define crossA 9 //White LED that allows pedestrians to crossA
#define buttonA 2

//Stoplight B Pin number definitions
#define stB_red 8
#define stB_yellow 7
#define stB_green 6
#define crossB 5 //Blue LED that allows pedestrians to crossB
#define buttonB 3

//Global Delay is 1s
#define Delay_time 1000

//This value is multiplied by the global delay
#define green_time 4 
#define yellow_time 2
#define red_time 3


//Keeps Track of the current Cycle and Pedestrian Flags
volatile int global_state;
volatile int FlagA;
volatile int FlagB;

//No Used
volatile int lightA_state; //green = 1, yellow = 2, red = 3
volatile int lightB_state; //green = 1, yellow = 2, red = 3
int i = 0;

void setup() {
 //Enabling Each Pin As IO
  pinMode(crossA, OUTPUT);
  pinMode(stA_red,OUTPUT);
  pinMode(stA_yellow, OUTPUT);
  pinMode(stA_green, OUTPUT);
  pinMode(buttonA, INPUT_PULLUP);
  //////////////////////////////////
  pinMode(crossB, OUTPUT);
  pinMode(stB_red,OUTPUT);
  pinMode(stB_yellow, OUTPUT);
  pinMode(stB_green, OUTPUT);
  pinMode(buttonB, INPUT_PULLUP);

 //Define the Pin to ISR
  attachInterrupt(digitalPinToInterrupt(buttonA),SetFlagA,CHANGE); //Attached the Interrupt subroutine
  attachInterrupt(digitalPinToInterrupt(buttonB),SetFlagB,CHANGE); //Attached the Interrupt subroutine

  Serial.begin(9600); //Used for debugging

 //Assigning Initial Value to variables
  FlagA=0;
  FlagB=0;
  global_state = 0;
}

void pedAoff(){ //Turns White LED for pedestrian A
  digitalWrite(crossA,LOW);
}

void pedAon(){// Turns on White LED so Pedestrian A can cross
  digitalWrite(crossA,HIGH);
}

void pedBoff(){// Turns off Blue LED for Pedestrian B
  digitalWrite(crossB,LOW);
}

void pedBon(){//Turns on Blue LED so Pedestrian B can cross
  digitalWrite(crossB,HIGH);
}

void doByState(){// Desiscion making function. Decides what to do based on the global_state variable
   switch (global_state) {
    case 0:{//EMERGENCY stoplights will blink
      for(i=0;i<8;i++){
        allOff();
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
      stAsetGreen();
      delay(Delay_time * green_time);
        break;
    }
    case 3:{//Stoplight A Yellow
      stAsetYellow();
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

void SetFlagA(void){// Pedestrian in A is waiting, CASE 8
  FlagA=1;
    Serial.println("INTERRUPT A");
}

void SetFlagB(void){// Pedestrian in B is waiting, CASE 9
  FlagB=1;
  Serial.println("INTERRUPT B");
}

void stAsetGreen(){//Stoplight A is set to Green
  stAoff();
  digitalWrite (stA_green,HIGH);
}

void stAsetYellow(){//Stoplight A is set to Yellow
  stAoff();
  digitalWrite(stA_yellow,HIGH);
}

void stAsetRed(){//Stoplight A is set to Red
  stAoff();
  digitalWrite(stA_red,HIGH);
}

void stBsetGreen(){//Stoplight B is set to Green
  stBoff();
  digitalWrite (stB_green,HIGH);
}

void stBsetYellow(){//Stoplight B is set to Yellow
  stBoff();
  digitalWrite(stB_yellow,HIGH);
}

void stBsetRed(){//Stoplight B is set to Red
  stBoff();
  digitalWrite(stB_red,HIGH);
}

void stAoff(){ //Turns off Stoplight A
  digitalWrite (stA_green,LOW);
  digitalWrite(stA_yellow,LOW);
  digitalWrite(stA_red,LOW);
  digitalWrite(crossA,LOW);
}

void stBoff(){//Turns off Stoplight B
  digitalWrite (stB_green,LOW);
  digitalWrite(stB_yellow,LOW);
  digitalWrite(stB_red,LOW);
  digitalWrite(crossB,LOW);
}

void allRed(){//All stoplights are set to Red
  allOff();
  digitalWrite(stA_red,HIGH);
  digitalWrite(stB_red,HIGH);
}

void allOff(){//All stoplights are set to off
  stAoff();
  stBoff();
}

void PedAroutine(){
      //Turn on cross light and hold
      pedAon();
      delay(Delay_time*5);

      //Start blinking the crossing light to warn time is over
      for(i=0;i<5;i++){
        pedAoff();
        delay(250);
        pedAon();
        delay(250);
      }

      //Turn off pedestrian crossing light
      pedAoff();
}

void PedBroutine(){
      //Turn on cross light and hold
      pedBon();
      delay(Delay_time*5);

      //Start blinking the crossing light to warn time is over
      for(i=0;i<5;i++){
        pedBoff();
        delay(250);
        pedBon();
        delay(250);
      }

      //Turn off pedestrian crossing light
      pedBoff();
}
   
void loop() {
    doByState();
    global_state = global_state + 1;
}




