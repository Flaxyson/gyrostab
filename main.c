#include "gd32vf103.h"
#include "delay.h"
#include "pwm.h"
#include "gd32v_mpu6500_if.h"
#include "PID.h"
#include "aTan.h"


int main(void){
    InitPWM();
    initServoA();
    int prev_time=0,current_time=0, delta_Time=0;
    int32_t gyroX,gyroY,accX,accY,roll=0,pitch=0;
    mpu_vector_t vecA, vecG;

    /* Initialize pins for I2C */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_I2C0);
    gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
    
    mpu6500_install(I2C0);
    //motorStartupSeq(0);
    
    while(1){
        prev_time = current_time;
        current_time = millis();
        delta_Time = current_time - prev_time;

        mpu6500_getGyroAccel(&vecG,&vecA);

        //65536/4000 = 16,3865
        //16,3865 << 8 = 1000001100010 = 4194
        //gyroX = vecG.x/16.4;
        
        accX = arctan(vecA.z , vecA.x);
        accY = arctan(vecA.z , -vecA.y);

        gyroX = -(delta_Time * (int)vecG.y << 16)/(4194*1000);   // Turns into fixed point 8 <<
        gyroY = -(delta_Time * (int)vecG.x << 16)/(4194*1000);

        //Complementary Filter
        roll = ((0.97*(gyroX+roll)) + (0.03*accX));
        pitch = ((0.97*(gyroY+pitch)) + (0.03*accY));  

        MoveServoA(roll);
        MoveServoB(pitch);
    }
}



