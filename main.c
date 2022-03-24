#include "gd32vf103.h"
#include "drivers.h"
#include "dac.h"
#include "pwm.h"
#include "pid.h"
#include "gyro.h"


int main(void){
    int key;
    int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};  //Ta bort i framtiden
    t5omsi();                               // Initialize timer5 1kHz
    colinit();                              // Initialize column toolbox
    l88init();                              // Initialize 88 led toolbox
    keyinit();                              // Initialize keyboard toolbox

    while (1) {
      if (t5expq()) {                     // Manage periodic tasks
          l88row(colset());               // ...88LED and Keyboard
           if ((key=keyscan())>=0) {       // ...Any key pressed?
                                            //Banana delicious?
                                            //Mmmmm vad gott <3<3
                                            //Yaaaasssss daddy
          }

      }
    }
}



