#include "gd32vf103.h"
#include "drivers.h"
#include "dac.h"
#include "pwm.h"


//************Funktioner**************************************//

//************MAIN*******************************************//

int main(void){
    int ms=0, s=0, key, pKey=-1, c=0, idle=0;
    int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};
    int dac=0, speed=0;
    int potens=0;


    t5omsi();                               // Initialize timer5 1kHz
    colinit();                              // Initialize column toolbox
    l88init();                              // Initialize 88 led toolbox
    keyinit();                              // Initialize keyboard toolbox
    DAC0powerUpInit();                      // Initialize DAC0/PA4 toolbox
    T1powerUpInitPWM(0x1);                  // Timer #1, Ch #2 PWM
    //T1powerUpInitPWM(0xC);                  // Timer #1, Ch #2 & 3 PWM
    T1setPWMmotorB(-50);


    while (1) {
            DAC0set(dac++);                 // DAC0 Unit test
            T1setPWMch2(15000);               // PWM T1/C2 Unit test
  }
}

