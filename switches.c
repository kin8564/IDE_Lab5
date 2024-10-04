/* 
Title: switches.c 
Purpose: Initialize MSP423 switches for I/O
Name: Kingsley Nwabeke  
Date: 9/24/24
  
*/
#include "msp.h" 

#include "Common.h"

#include <stdio.h>

#include "switches.h"

void Switch1_Init(void)
{
	// configure PortPin for Switch 1 and Switch2 as port I/O
	P1SEL0 &= ~BIT1;
	P1SEL1 &= ~BIT1;
	
	// configure as input (pullup)
	P1DIR &= ~BIT1;
	P1REN |= BIT1;
	P1OUT |= BIT1;	
	
}
void Switch2_Init(void)
{
	// configure PortPin for Switch 1 and Switch2 as port I/O
	P1SEL0 &= ~BIT4;	
	P1SEL1 &= ~BIT4;
	
	//configure as input (pullup)
	P1DIR &= ~BIT4;
	P1REN |= BIT4;
	P1OUT |= BIT4;
	
}
/*
------------Switch_Input------------
 Read and return the status of Switch1
 Input: none
 return: TRUE if pressed
         FALSE if not pressed
*/
BOOLEAN Switch1_Pressed(void)
{
	BOOLEAN retVal = FALSE;
	// check if pressed
	if ((P1IN & BIT1) == 0) {
		retVal = TRUE;
		P1IFG |= BIT1;							// generate an interrupt
	}
	return (retVal);              // return TRUE(pressed) or FALSE(not pressed)
}
/*
------------Switch_Input------------
 Read and return the status of Switch2
 Input: none
 return: TRUE if pressed
         FALSE if not pressed
*/
BOOLEAN Switch2_Pressed(void)
{
	BOOLEAN retVal = FALSE;
	// check if pressed
	if ((P1IN & BIT4) == 0) {
		retVal = TRUE;
		P1IFG |= BIT4;							// generate an interrupt
	}
	return (retVal);              // return TRUE(pressed) or FALSE(not pressed)
}
