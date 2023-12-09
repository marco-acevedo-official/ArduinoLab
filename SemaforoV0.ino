/****************************************************/
/* Laboratoy No 2 trafic light with pedestrian Light*/
/*                        Roman Lopez Ph. D.        */
/****************************************************/  
/*
#define cross 9
#define red 12
#define yellow 11
#define green 10
#define button 2
*/

#define cross 5
#define red 8
#define yellow 7
#define green 6
#define button 2

#define Delay_time 500
#define Green_time 5
#define Yellow_time 3
#define Red_time 5

volatile int button_state = 0;
int i = 0;
int Flag;
int Ligth_State;

/*
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
*/
void setup() {
  pinMode(cross, OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(button),SetFlag,CHANGE); //Attached the Interrup subroutine
  Serial.begin(9600);    
  Flag=0;
   }
   
void loop() {
   LOOP:
      //Set the state flag, 1=gree,2=yellow and 3=red
     //Set Green ON, ref and Yellow OFF
    // Green State
        digitalWrite(red,LOW); 
        digitalWrite(yellow,LOW);
        digitalWrite(green,HIGH);
        digitalWrite(cross,LOW);
        for (i=0;i<=Green_time;i++)
          {delay(Delay_time);
           if(Flag==1) {
            Ligth_State=1;
            Pedestian();
            goto LOOP;
            }
          }
         
     //Yellow State
        digitalWrite(green,LOW); 
        digitalWrite(yellow,HIGH); 
        for (i=0;i<=Red_time;i++)
          {delay(Delay_time);
           if(Flag==1) {
            Ligth_State=2;
            Pedestian();
            goto LOOP;
            }
          }
     
        // Red State
        digitalWrite(yellow,LOW); 
        digitalWrite(red,HIGH); 
        for (i=0;i<=Yellow_time;i++)
          {delay(Delay_time);
           if(Flag==1) {
            Ligth_State=3;
            Pedestian();
             goto LOOP;
             }
          }       
}
void SetFlag(void)
  {
     Flag=1;
  }
   
void Pedestian(void){
   switch (Ligth_State) {
      case 1:{// Off green on Yellow
        digitalWrite(green,LOW); //off Green set Yellow
        digitalWrite(yellow,HIGH);
        delay(2000);
        // Set Red on and Pedestrian on
        digitalWrite(yellow,LOW); //off Green set Yellow
        digitalWrite(red,HIGH);
        digitalWrite(cross,HIGH);
        delay(5000);   
        break;
        }
    case 2:{//YELLOW state
        //
        delay(500); //Keep yellow for 1/2 second
        delay(1000);
        // Set Red on and Pedestrian on
        digitalWrite(yellow,LOW); //off Green set Yellow
        digitalWrite(red,HIGH);
        digitalWrite(cross,HIGH);
        delay(5000);     
        break;
        }       
    case 3:{//Pedestrian on, red on
        digitalWrite(red,HIGH);
        digitalWrite(cross,HIGH);
        delay(3000);
        break;
        }
     default:{};
      }
      for (i=0;i<=5;i++)
        {digitalWrite(cross,LOW);
        delay(1000);
        digitalWrite(cross,HIGH);
        delay(1000);
        }
  Flag=0;   
}
