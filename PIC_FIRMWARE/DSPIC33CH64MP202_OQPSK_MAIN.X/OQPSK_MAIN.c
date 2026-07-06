///*
// * File:   OQPSK_MAIN.c
// * Author: kojim
// *
// * Created on 2026/07/03, 21:00
// */
//
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
    
//    //AUXILIARY PLL : 1000MHz = 8MHz * 125
    APLLFBD1 = 125;
    APLLDIV1bits.AVCODIV = 2;//AFVCO / 2V
	// DAC用クロック設定：500MHz( AFPLLO = (8 * M) / (N1 * N2 * N3) )
    
//	APLLFBD1bits.APLLFBDIV = 125; // M
//	ACLKCON1bits.APLLPRE = 1;	// N1
//	APLLDIV1bits.APOST1DIV = 2;	// N2 (1～7, must POST1DIVx >= POST2DIVx def:4)
//	APLLDIV1bits.APOST2DIV = 1;	// N3 (1～7, must POST1DIVx >= POST2DIVx def:1)
    
    //PORT SETTING -------------------------------------------------------------
    TRISA = 0x0000;
    ANSELA = 0x0001;//RA0:ANALOG
    LATA = 0x0002;
    
   /*
    * 本当はDACで出力したかったんだけど，使ってるマイコンのDACが死にかけなのかうまく出力できないから，
    * シリアルで出力して，シリアルプロッタで表示するようにした
    * ただし，データ形式は，uint16_tになる．
    */
    
    //UART SETTING -------------------------------------------------------------
    U1MODE = 0x8080;//UART1:EN, HIGHT BAUD RATTE MODE, Asynchronous 8-bit UART
    U1MODEH = 0x0800;//Uses fractional Baud Rate Generation, FOSC/2 (FP)
    
    
    
    while (1){
        
//        LATB ^= 0x0004;
        LATA ^= 0x0004;
        __delay_ms(100);
    }
    
    
    return 0;
}