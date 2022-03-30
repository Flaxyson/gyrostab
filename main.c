#include "gd32vf103.h"
#include "drivers.h"
#include "dac.h"
#include "pwm.h"


//************Funktioner**************************************//

//************MAIN*******************************************//

int main(void){
    
    DAC0powerUpInit();                      // Initialize DAC0/PA4 toolbox
    T1powerUpInitPWM(0x1);                  // Timer #1, Ch #2 PWM
    
    while (1) {
      T1setPWMmotorB(-50);
  }
}

