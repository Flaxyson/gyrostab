#include "gd32vf103.h"
#include "drivers.h"
#include "dac.h"
#include "pwm.h"

#define ROW 8 

//************Funktioner**************************************//

//************MAIN*******************************************//
int main(void){
  int ms=0, s=0, key, idle=0;
  int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};


  t5omsi();                               // Initialize timer5 1kHz
  colinit();                              // Initialize column toolbox
  l88init();                              // Initialize 8*8 led toolbox
  keyinit();                              // Initialize keyboard toolbox
  DAC0powerUpInit();                      // Initialize DAC0/PA4 toolbox
  T1powerUpInitPWM(0x1);                  // Timer #1, Ch #2 PWM
  T1powerUpInitPWM(0xC);                  // Timer #1, Ch #2 & 3 PWM

  while(1){
    //idle++;                             // Manage Async events
    if(t5expq()){                         // Manage periodic tasks
      l88row(colset());                   // ...8*8LED and Keyboard
      ms++;                               // ...One second heart beat
      if (ms==1000){
        ms=0;
      }
      if ((key=keyscan())>=0){            // ...Any key pressed?

        

      } 
    }
  }
}

