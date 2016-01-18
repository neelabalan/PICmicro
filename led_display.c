#include "led_display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #BYTE T2CON = 0X12
// #BYTE ccp1con = 0x15
// #byte pie1 = 0x8c
int16 Count  = 123;
int16 Msec   = 0;
int8  digit1 = 0;
int8  digit2 = 0;
int8  digit3 = 0;

//{0x7E,0X30,0X6D,0X79,0X33,0X5B,0X5F,0X70,0X7F,0X7B};
unsigned int8 segment_code[11] = {
    0x3f, 0X06, 0X5b, 0X4f, 0X66, 0X6d,
    0X7d, 0X07, 0X7f, 0X6f, 0
}; 

void display(void);
void run(void);
void current_cal(void);
void measure_current(void);
float sine_convert(void);

#int_TIMER2
TIMER2_isr()
{
    MSec++;
    if (MSec > 100)
    {
        MSec = 0;
        Count++;
    }
    if (Count > 100)
    {
        Count = 0;
    }
    set_timer2(0);
    T2CON = 0;
}

#int_TIMER0
TIMER0_isr()
{
    set_timer0(0);
}

void main()
{

    output_low(PIN_A5);
    T2CON = (32) | 7;
    ccp1con = 4;

    setup_adc_ports(AN0_AN1_AN3);
    setup_adc(ADC_CLOCK_INTERNAL);
    setup_spi(FALSE);
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_1);
    setup_wdt(WDT_72MS);
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_4);
    setup_timer_2(T2_DIV_BY_16, 255, 16);
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
    setup_ccp1(CCP_CAPTURE_rE);
    set_adc_channel(0);
    // trisa4 = 1;

    delay_ms(2000);

    set_tris_c(0xf0);

    enable_interrupts(INT_CCP1);
    delay_ms(250);
    enable_interrupts(INT_TIMER2);
    enable_interrupts(INT_TIMER0);
    enable_interrupts(GLOBAL);

    delay_ms(200);
    while (1)
    {

        digit1 = segment_code[((Count % 1000) / 100)];
        digit2 = segment_code[((Count / 10) % 100) / 10];
        digit3 = segment_code[(Count / 10) % 10];
        display();
    }
}

void display(void)
{
    //  if(display_count1==0)
    {
        output_b(digit1);
        OUTPUT_HIGH(PIN_C1);
        DELAY_us(1000);
        OUTPUT_LOW(PIN_C1);
        OUTPUT_B(0);
    }
    //  if(display_count1==1)
    {
        output_b(digit2);
        OUTPUT_HIGH(PIN_C3);
        DELAY_us(1000);
        OUTPUT_LOW(PIN_C3);
        OUTPUT_B(0);
    }
    //  if(display_count1==2)
    {
        output_b(digit3);
        OUTPUT_HIGH(PIN_C0);
        DELAY_us(1000);
        OUTPUT_LOW(PIN_C0);
        OUTPUT_B(0);
    }
    // msb2  = ((int16)dispval%1000)/100;
    // msb1  = ((int16)dispval%100)/10;
    // lsb   = (int16)dispval%10;
}

