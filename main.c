#include "stdio.h"
#include "gd32vf103.h"
#include "delay.h"
#include "pwm.h"
#include "gd32v_mpu6500_if.h"
#include "PID.h"
#include "aTan.h"

#define PI 3.14159265

int main(void){
    T1powerUpInitPWM();
    initServoA();
    //T1setPWMmotorA(0);
    //T1setPWMmotorB(0);
    
    int AngleX=0;
    mpu_vector_t vecA, vecG;

    /* Initialize pins for I2C */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_I2C0);
    gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
    /* Initialize the IMU (Notice that MPU6500 is referenced, this is due to the fact that ICM-20600
       ICM-20600 is mostly register compatible with MPU6500, if MPU6500 is used only thing that needs 
       to change is MPU6500_WHO_AM_I_ID from 0x11 to 0x70. */
    mpu6500_install(I2C0);

    

    while(1){

        mpu6500_getAccel(&vecA);


        moveServo(arctan(vecA.z , vecA.x));
        //moveServo(-90);  //-90 grader
        //moveServo(0);   // 0 grader
        //moveServo(90);  //90 grader
        //delay_1ms(20000);
        //moveServo(0); //-1100 till +1100
        
    }
}



