#include "pwm.h"

/****************************PWM-CODE************************************/

void T1powerUpInitPWM(void){
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
    rcu_periph_clock_enable(RCU_TIMER1);

    timer_deinit(TIMER1);
    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler         = 107;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 15999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1, &timer_initpara);

    timer_channel_output_struct_para_init(&timer_ocinitpara);
    timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER1,TIMER_CH_0,&timer_ocinitpara);
    timer_channel_output_config(TIMER1,TIMER_CH_1,&timer_ocinitpara);
    timer_channel_output_config(TIMER1,TIMER_CH_2,&timer_ocinitpara);
    timer_channel_output_config(TIMER1,TIMER_CH_3,&timer_ocinitpara);

    
    timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_0,11999);
    timer_channel_output_mode_config(TIMER1,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_1,11999);
    timer_channel_output_mode_config(TIMER1,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,11999);
    timer_channel_output_mode_config(TIMER1,TIMER_CH_2,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,11999);
    timer_channel_output_mode_config(TIMER1,TIMER_CH_3,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
    
    
    timer_auto_reload_shadow_enable(TIMER1);
    timer_enable(TIMER1);
}

void T1setPWMch2(int value){
    timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,value);
}

void T1setPWMmotorA(int throttel){
    if (throttel<0) {
       timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_1,(-throttel/100.0)*16000);
       timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_0,0);
    } else {
       timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_1,0);
       timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_0,(throttel/100.0)*16000);
    }
}

void T1setPWMmotorB(int throttel){
    if (throttel>0) {
       timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,(throttel/100.0)*16000);
       timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,0);
    } else {
       timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,0);
       timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,(-throttel/100.0)*16000);
    }
}


/****************************SERVO-CODE************************************/

void initServoA(void){
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_TIMER0);

    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    timer_parameter_struct timer_initpara;
    timer_initpara.prescaler         = 107;                         //SCALE CLOCK TO 1MHz
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER0, &timer_initpara);

    timer_oc_parameter_struct timer_ocinitpara;
    timer_ocinitpara.outputstate    = TIMER_CCX_ENABLE;
    timer_ocinitpara.outputnstate   = TIMER_CCXN_DISABLE;
    timer_ocinitpara.ocpolarity     = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity    = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate    = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate   = TIMER_OC_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER0, TIMER_CH_0, &timer_ocinitpara);

    timer_autoreload_value_config(TIMER0, 19999);                   //PERIOD IS 50MS LONG

    timer_channel_output_mode_config(TIMER0, TIMER_CH_0, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
    timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 1000);

    timer_primary_output_config(TIMER0, ENABLE);
    timer_enable(TIMER0);
}

void moveServo(int degrees){
    timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, degrees+1000);
}