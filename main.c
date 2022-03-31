#include "gd32vf103.h"
#include "delay.h"
#include "pwd.h"
#include "servo.h"




int main(void){
    T1powerUpInitPWM();
    USART0_init();                             // Initialize USART0 toolbox
    initServoA();


    while(1){
      
        T1setPWMmotorB(-60);
        T1setPWMmotorA(-60);

        moveServo(1000);
        delay_1ms(1000);

        moveServo(2048);
        delay_1ms(1000);

        moveServo(3000);
        delay_1ms(1000);

        moveServo(2048);
        delay_1ms(1000);

    }

}
