/*
 * File:   OQPSK_MAIN.c
 * Author: kojim
 *
 * Created on 2026/07/03, 21:00
 */

#include "Configuration.h"
#include <xc.h>
#include <stdint.h>
#include "OQPSK_LUT.h"


#define FCY 90000000UL//90MHz
#include <libpic30.h>


int main(void) {
    //WDT SETTING --------------------------------------------------------------
    WDTCONLbits.ON = 0;//WDT:DISABLE
    
    //SYSTEM SETTING -----------------------------------------------------------
    
    //OSC SETTING --------------------------------------------------------------
    //MAIN PLL : FOSC:180MHz = FPLL / 2
    //8MHz * 90 / 2 / 1 = 360MHz
    //PRIMARY PLL
    CLKDIV = 0x0001;//PLLPRE 1:1
    PLLFBD = 90;
    PLLDIVbits.POST1DIV = 2;
    PLLDIVbits.POST2DIV = 1;
    
    //AUXILIARY PLL : 1000MHz = 8MHz * 125
    APLLFBD1 = 125;
    APLLDIV1bits.AVCODIV = 2;//AFVCO / 2
    
    
    //PORT SETTING -------------------------------------------------------------
    TRISA = 0x0000;
    ANSELA = 0x0001;//RA0:ANALOG
    LATA = 0x0002;
    
    //DAC SETTING --------------------------------------------------------------
    DACCTRL1L = 0x0040;//CLK:AFVCO/2, CLKDIV:1x
    
    
    while (1){
        LATA ^= 0x0004;
        __delay_ms(500);
    }
    
    
    return 0;
}