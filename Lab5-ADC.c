/*
* Rochester Institute of Technology
* Department of Computer Engineering
* CMPE 460  Interfacing Digital Electronics
* LJBeato
* 1/14/2021
*
* Filename: main_timer_template.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "msp.h"
#include "uart.h"
#include "leds.h"
#include "switches.h"
#include "Timer32.h"
#include "CortexM.h"
#include "Common.h"
#include "ADC14.h"
// The sprintf function seemed to cause a hange in the interrupt service routine.
// I think if we increase the HEAP size, it will work
// change to Heap_Size       EQU     0x00000200 in startup_msp432p401r_uvision.s


BOOLEAN Timer1RunningFlag = FALSE;
BOOLEAN Timer2RunningFlag = FALSE;

unsigned long MillisecondCounter = 0;



// Interrupt Service Routine for Timer32-1
void Timer32_1_ISR(void)
{
	  char temp[64];
	  unsigned int analogIn = 0;
			
		analogIn = ADC_In();
	
		//Print decimal
	  uart0_put("\n\rDecimal Value: ");
		sprintf(temp, "%i", analogIn);
		uart0_put(temp); 
	
	  //Print HEX
	  uart0_put("\n\rHex Value: 0x");
	  sprintf(temp, "%X", analogIn);
	  uart0_put(temp); 
		//ADC14->CTL0 &= 0x00000000;
		
		
	
		
}
// Interrupt Service Routine
void Timer32_2_ISR(void)
{

}



// main
int main(void)
{
	//char temp[64];
	//unsigned int analogIn = 0;
	//initializations
	uart0_init();
	uart0_put("\r\nLab5 ADC demo\r\n");

	Timer32_1_Init(&Timer32_1_ISR, CalcPeriodFromFrequency(2), T32DIV1); // initialize Timer A32-1;

	LED1_Init();
	LED2_Init();
	Switch2_Init();
	ADC0_InitSWTriggerCh6();
	EnableInterrupts();
	while(1)
	{
   WaitForInterrupt();	
  }
}

