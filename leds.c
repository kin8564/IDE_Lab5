/* 
Title: leds.c 
Purpose: Initialize MSP423 LEDs for I/O
Name: Kingsley Nwabeke  
Date: 9/24/24
  
*/
#include "msp.h" 

#include "Common.h"

#include <stdio.h>

void LED1_Init(void)
{
	// configure PortPin for LED1 as port I/O 
	P1SEL0 &= ~BIT0; // select Port1 Bit0 for use as port I/O
	P1SEL1 &= ~BIT0;

	// make built-in LED1 LED high drive strength
	P1DS |= BIT0; // set high drive strength

	// make built-in LED1 out	 
	P1DIR |= BIT0; // set BIT 0 as output

	// turn off LED
	P1OUT &= ~BIT0;  // set P1.0 to ‘0’
}

void LED2_Init(void)
{
	// configure PortPin for LED2 as port I/O 
	P2SEL0 &= ~BIT0; // select Port2 Bit0 for use as port I/O
	P2SEL1 &= ~BIT0;
	
	P2SEL0 &= ~BIT1;
	P2SEL1 &= ~BIT1;
	
	P2SEL0 &= ~BIT2;
	P2SEL1 &= ~BIT2;

	// make built-in LED2 LEDs high drive strength
	P2DS |= BIT0;
	P2DS |= BIT1;
	P2DS |= BIT2;

	// make built-in LED2 out	 
	P2DIR |= BIT0;
	P2DIR |= BIT1;
	P2DIR |= BIT2;

	// turn off LED
	P2OUT &= ~BIT0;
	P2OUT &= ~BIT1;
	P2OUT &= ~BIT2;
}
BOOLEAN LED1_State(void) {
	if ((P1OUT & BIT0) == 1) {
		return TRUE;
	}
	return FALSE;
}
BOOLEAN LED2_State(void) {	//only checks RED, add other colors if needed
	if ((P2OUT & BIT0) == 1) { 
		return TRUE;
	}
	return FALSE;
}
void LED1_On(void) {
	P1OUT |= BIT0;
}
void LED1_Off(void) {
	P1OUT &= ~BIT0;
}
void LED2_On(int color) {
	P2OUT |= color;
}
void LED2_Off() {
	P2OUT &= ~BIT0;	// Turn off LED2_RED
	P2OUT &= ~BIT1;	// Turn off LED2_GREEN
	P2OUT &= ~BIT2;	// Turn off LED2_BLUE
}
void Loop_Delay(void){
	int i;
	int j = 0;
	for(i = 0; i < 100000; i++){
		j++;
	}
}