/****************************************************/
/* Laboratoy No 2 trafic light with pedestrian Light*/
/*                        Roman Lopez Ph. D.        */
/****************************************************/  
 
//Pin number definitions
#define stA_red 12
#define stA_yellow 11
#define stA_green 10
#define crossA 9 //White LED that allows pedestrians to crossA
#define buttonA 2

#define Delay_time 1000 //milis

#define green_time 4 //int i 
#define yellow_time 4
#define red_time 4

volatile int buttonA_state = 0;

int i = 0;
int FlagA;
volatile int lightA_state; //green = 1, yellow = 2, red = 3

//Interrupt Routine for buttonA
//void checkSwitch() {
//  if (digitalRead(buttonA) == LOW) {
//    buttonA_state = 1;
//    //Serial.println("buttonA State == LOW");
//  }
//}

void setup() {
  pinMode(crossA, OUTPUT);//9
  pinMode(stA_red,OUTPUT);//12
  pinMode(stA_yellow, OUTPUT);//11
  pinMode(stA_green, OUTPUT);//10
  pinMode(buttonA, INPUT_PULLUP);//2

  attachInterrupt(digitalPinToInterrupt(2),SetFlagA,CHANGE); //Attached the Interrup subroutine

  Serial.begin(9600);

  FlagA=0;

  //attachInterrupt(digitalPinToInterrupt(buttonA),checkSwitch,FALLING);
}
   
void loop() {
   LOOP:
        //Set the state FlagA, 1=stA_green, 2=stA_yellow and 3=stA_red
        //Set stA_green ON, ref and stA_yellow OFF
  //-----------------------------------------------------------------------
        // stA_green State
        stAsetGreen();
        for (i=0;i< green_time;i++)
        {
          delay(Delay_time);
          if(FlagA==1) {
            lightA_state=1;
            PedestrianA();
            goto LOOP;
          }
        }
  //-----------------------------------------------------------------------        
        //stA_yellow State
        stAsetYellow();
        for (i=0;i<=red_time;i++)
        {
          delay(Delay_time);
          if(FlagA==1) {
            lightA_state=2;
            PedestrianA();
            goto LOOP;
          }
        }
  //-----------------------------------------------------------------------     
        // stA_Red State
        stAsetRed();
        for (i=0;i<=yellow_time;i++)
        {
          delay(Delay_time);
          if(FlagA==1) {
            lightA_state=3;
            PedestrianA();
            goto LOOP;
          }
        }       
}

void SetFlagA(void){
  FlagA=1;
}

void PedestrianA(void){
   switch (lightA_state) {
      case 1:{//Stoplight A is Green
        // Off stA_green on stA_yellow
        digitalWrite (stA_green,LOW); //off stA_green set stA_yellow
        digitalWrite(stA_yellow,HIGH);
        delay(2000);
        // Set stA_Red on and Pedestrian on
        digitalWrite(stA_yellow,LOW); //off stA_green set stA_yellow
        digitalWrite(stA_red,HIGH);
        digitalWrite(crossA,HIGH);
        delay(5000);   
        break;
      }
  //-----------------------------------------------------------------------
    case 2:{//Stoplight A is Yellow
        //stA_yellow state
        delay(500); //Keep stA_yellow for 1/2 second
        delay(1000);
        // Set stA_Red on and Pedestrian on
        digitalWrite(stA_yellow,LOW); //off stA_green set stA_yellow
        digitalWrite(stA_red,HIGH);
        digitalWrite(crossA,HIGH);
        delay(5000);     
        break;
      }
  //-----------------------------------------------------------------------    
    case 3:{//Stoplight A is red
      //Pedestrian on, stA_red on
        digitalWrite(stA_red,HIGH);
        digitalWrite(crossA,HIGH);
        delay(5000);
        break;
      }
  //-----------------------------------------------------------------------
     default:{};
    }//end Switch
  //-----------------------------------------------------------------------
      for (i=0;i<=3;i++)
      {
        digitalWrite(crossA,LOW);
        delay(1000);
        digitalWrite(crossA,HIGH);
        delay(1000);
      }
        digitalWrite(crossA,LOW);
        delay(1000);

  FlagA=0;   
}

void stAsetGreen(){
  stAoff();
  digitalWrite (stA_green,HIGH);
}

void stAsetYellow(){
  stAoff();
  digitalWrite(stA_yellow,HIGH);
}

void stAsetRed(){
  stAoff();
  digitalWrite(stA_red,HIGH);
}

void stAoff(){
  digitalWrite (stA_green,LOW);
  digitalWrite(stA_yellow,LOW);
  digitalWrite(stA_red,LOW);
  digitalWrite(crossA,LOW);
}
