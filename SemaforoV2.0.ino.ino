/****************************************************/
/* Laboratoy No 2 trafic light with pedestrian Light*/
/*                        Roman Lopez Ph. D.        */
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
#define crossB 5 //Blue LED that allows pedestrians to crossA
#define buttonB 3

#define Delay_time 1000 //milis

#define green_time 4 //int i 
#define yellow_time 4
#define red_time 4

int i = 0;
int j,k;
int FlagA;
int FlagB;

volatile int global_state = 0;
volatile int lightA_state; //green = 1, yellow = 2, red = 3
volatile int lightB_state; //green = 1, yellow = 2, red = 3

void setup() {
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

  attachInterrupt(digitalPinToInterrupt(2),SetFlagA,CHANGE); //Attached the Interrup subroutine
  attachInterrupt(digitalPinToInterrupt(3),SetFlagB,CHANGE); //Attached the Interrup subroutine

  Serial.begin(9600);

  FlagA=0;
  FlagB=0;
  global_state = 0;
}

void pedAoff(){
  digitalWrite(crossA,LOW);
}

void pedAon(){
  digitalWrite(crossA,HIGH);
}

void pedBoff(){
  digitalWrite(crossB,LOW);
}

void pedBon(){
  digitalWrite(crossB,HIGH);
}

void doByState(){
   switch (global_state) {
    case 0:{//EMERGENCY
      for(i=0;i<8;i++){
      allOff();
      delay(250);
      allRed();
      delay(250);
  }
      break;
    }
      case 1:{//All Red
        delay(Delay_time*red_time);
        break;
      }
  //-----------------------------------------------------------------------
    case 2:{//Stoplight A Green
      stAsetGreen();
      delay(Delay_time * green_time);
        break;
    }
  //-----------------------------------------------------------------------    
    case 3:{//Stoplight A Yellow
      stAsetYellow();
      delay(Delay_time * yellow_time);
      break;
    }
    
    case 4:{//Stoplight A Red
      stAsetRed();
      delay(Delay_time * red_time);
      break;
    }
  ///////////////////////////////////////////////////////////////////////////
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
    case 7:{//Stoplight B Red
      stBsetRed();
      delay(Delay_time * red_time);

      if((FlagA + FlagB) > 0){//Pedestrian is Waiting
        if((FlagA + FlagB) == 2){
          break;
        }else{
          global_state = 9;
        }

      }else{
        global_state = 1;
      }
      //FLAG A + FLAG B >0? No -> global_state = 2 check for ++; YES -> if A case 8
      break;
    }

    case 8:{//Pedestrian A Waiting
      FlagA = 0;
      pedAon();
      delay(Delay_time*2);
      pedAoff();
      //if also B go to case 9, else case 2
      if(FlagB == 1){global_state = 9;}else{global_state = 1;}
      break;
    }

    case 9:{//Pedestrian B Waiting
      FlagB = 0;
      pedBon();
      delay(Delay_time*2);
      pedBoff();
      global_state = 1;
      break;
    }
  //-----------------------------------------------------------------------
     default:{

      //go to case 0
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
   
void loop() {
    doByState();
    global_state = global_state + 1;
}




