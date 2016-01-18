#include <16F876A.h>
#device *=16
#device ICD=true
#device adc=10
#use delay(clock=16000000,restart_wdt)
#fuses noWDT, HS, PUT, PROTECT, DEBUG, BROWNOUT, NOLVP, noCPD, noWRT

#BYTE T2CON = 0X12
#BYTE ccp1con = 0x15
#byte pie1 = 0x8c
   