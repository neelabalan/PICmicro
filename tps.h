#include <16F873A.h>
#device ICD=TRUE
#device adc=8

#FUSES NOWDT           // No Watch Dog Timer
#FUSES HS              // High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES noPUT           // Power Up Timer
#FUSES PROTECT         // Code not protected from reading
#FUSES BROWNOUT        // No brownout reset

#use delay(clock=16000000)
