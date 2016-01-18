#include "tps.h"
#include "math.h"
const float sine_ary[37] = {
    1,      0.83,   0.66, 
    0.50,   0.36,   0.23, 
    0.13,   0.06,   0.02, 
    0,      0.02,   0.06, 
    0.13,   0.23,   0.36, 
    0.5,    0.66,   0.82, 
    1,      1.17,   1.34, 
    1.50,   1.64,   1.76, 
    1.86,   1.94,   1.98, 
    2,      1.98,   1.87, 
    1.77,   1.65,   1.50, 
    1.35,   1.18
};

const float anti_sine_ary[37] = {
    1,      1.17,   1.34, 
    1.50,   1.64,   1.76, 
    1.86,   1.94,   1.98, 
    2,      1.98,   1.87, 
    1.77,   1.65,   1.50, 
    1.35,   1.18,   1, 
    0.83,   0.66,   0.50, 
    0.36,   0.23,   0.13, 
    0.06,   0.02,   0, 
    0.02,   0.06,   0.13, 
    0.23,   0.36,   0.5, 
    0.66,   0.82
};

int8  angle     = 0;
int16 duty      = 200;
int1  once      = 1;
int8  count     = 0;
float sine_duty = 0;

#int_TIMER1
TIMER1_isr()
{
    angle = angle + 1;
    if (angle > 34)
    {
        angle = 0;
    }

    set_timer1(64964);
}

#int_TIMER0
TIMER0_isr()
{
    if (count < 2)
        count++;

    if (count == 2)
        output_high(pin_a0);
    // delay_us(1);
    // output_low(pin_a0);
    set_timer0(152);
}
void main()
{

    setup_spi(SPI_SS_DISABLED);
    // setup_timer_0(RTCC_INTERNAL|RTCC_DIV_128|RTCC_8_bit);
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); // 256
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_4);
    // enable_interrupts(INT_RDA);
    setup_timer_2(T2_DIV_BY_1, 199, 1);
    setup_ccp1(CCP_PWM);
    // set_pwm1_duty(400);
    set_timer1(64535);

    enable_interrupts(int_timer1);
    disable_interrupts(INT_SSP);
    enable_interrupts(GLOBAL);

    if (once)
    {
        delay_ms(200);
        once = 0;
        enable_interrupts(int_timer0);
    }
    while (1)
    {
        sine_duty = (sine_ary[angle] * 100);
        duty = (long)sine_duty;
        set_pwm1_duty(duty);
    }
}