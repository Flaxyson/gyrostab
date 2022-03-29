#include "gd32vf103.h"
#include "drivers.h"
#include "dac.h"
#include "pwm.h"

#define ROW 8 

//************Funktioner**************************************//
int speedSetting(int aLookUpTbl[], int aKey, int aSpeed);
void speedPositive(int aRows[]);
void speedNegative(int aRows[]);

//************MAIN*******************************************//
int main(void){
  int ms=0, s=0, key, idle=0;
  int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};
  int dac=0;
  int speed = 0;

  //******************Bitvärden för siffrorna****************//
  int four[ROW]={0,68,68,68,124,4,4,4};
  int three[ROW]={0,56,68,4,24,4,68,56};
  int two[ROW]={0,56,68,4,8,16,32,124}; 
  int one[ROW]={0,8,24,8,8,8,8,28}; 
  int b[ROW]={0,56,36,36,56,36,36,56};

  t5omsi();                               // Initialize timer5 1kHz
  colinit();                              // Initialize column toolbox
  l88init();                              // Initialize 8*8 led toolbox
  keyinit();                              // Initialize keyboard toolbox
  DAC0powerUpInit();                      // Initialize DAC0/PA4 toolbox
  T1powerUpInitPWM(0x1);                  // Timer #1, Ch #2 PWM
  T1powerUpInitPWM(0xC);                  // Timer #1, Ch #2 & 3 PWM

  for(int i=0; i<8; i++){                 //Släcker 8x8
    l88mem(i, 0);
  }

  while(1){
    //idle++;                             // Manage Async events
    if(t5expq()){                         // Manage periodic tasks
      l88row(colset());                   // ...8*8LED and Keyboard
      ms++;                               // ...One second heart beat
      if (ms==1000){
        ms=0;
      }
      if ((key=keyscan())>=0){            // ...Any key pressed?

        speed = speedSetting(lookUpTbl, key, speed); //Räknar upp och ner variablen speed beroende på knapptryckning

        switch (speed){                   //Beroende på vilket state vi befinner oss i visar 8x8 nuvarande hastighet
        case -4: speedNegative(four);
          break;
        case -3: speedNegative(three);
          break;
        case -2: speedNegative(two);
          break;
        case -1: speedNegative(one);
          break;
        case 0:  speedPositive(b);
          break;
        case 1:  speedPositive(one);
            break;
        case 2:  speedPositive(two);
          break;
        case 3:  speedPositive(three);
          break;
        case 4:  speedPositive(four);
          break;  
        }
      } 
    }
    //l88mem(2,idle>>8);                  // ...Performance monitor
    //l88mem(3,idle); idle=0;
    //DAC0set(dac++);                     // DAC0 Unit test
    //T1setPWMch2(15000);                 // PWM T1/C2 Unit test
  }
}

int speedSetting(int aLookUpTbl[], int aKey, int aSpeed){
  if(aLookUpTbl[aKey]==1 && aSpeed>-4){
    aSpeed--;  
  }else if(aLookUpTbl[aKey]==2){
    aSpeed = 0;
  }else if(aLookUpTbl[aKey]==3 && aSpeed<4){
    aSpeed++;
  }
  return aSpeed;
}

void speedPositive(int aRows[]){
  for(int i=0; i<8; i++){
    l88mem(i, aRows[i]);
  }
}

void speedNegative(int aRows[]){
  for(int i=0; i<8; i++){
    l88mem(i, ~aRows[i]);
  }
}
