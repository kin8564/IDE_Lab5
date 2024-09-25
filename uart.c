/*
 * File:        uart.c
 * Purpose:     Provide UART routines for serial IO
 *
 * Notes:		
 *
 */

#include "msp.h"
#include "uart.h"  // you need to create this file with the function prototypes
#include "Common.h"  // from Lab1 code

#define BAUD_RATE 9600      //default baud rate 
extern uint32_t SystemCoreClock;  // clock rate of MCU


void uart0_init()
{
	uint32_t N;
	//Set the UART to RESET state (set bit0 of EUSCI_A0->CTLW0 register to '1'
	UCA0CTLW0 |= BIT0;

	// bit15=0,      no parity bits
	// bit14=x,      not used when parity is disabled
	// bit13=0,      LSB first
	// bit12=0,      8-bit data length
	// bit11=0,      1 stop bit
	// bits10-8=000, asynchronous UART mode
	// bits7-6=11,   clock source to SMCLK
	// bit5=0,       reject erroneous characters and do not set flag
	// bit4=0,       do not set flag for break characters
	// bit3=0,       not dormant
	// bit2=0,       transmit data, not address (not used here)
	// bit1=0,       do not transmit break (not used here)
	// bit0=1,       hold logic in reset state while configuring

	// set CTLW0 - hold logic and configure clock source to SMCLK
	UCA0CTLW0 |= BIT7;
	UCA0CTLW0 |= BIT6;

	// baud rate
	// N = clock/baud rate = clock_speed/BAUD_RATE
	// set BRW register
	N = SystemCoreClock / BAUD_RATE;
	UCA0BRW = N;

	// clear first and second modulation stage bit fields
	// MCTLW register;  
	UCA0MCTLW &= 0x000F; // clear bits 15 - 4
	

	// P1.3 = TxD
	// P1.2 = RxD
	// we will be using P1.2, P1.3 for RX and TX but not in I/O mode, so we set Port1 SEL1=0 and SEL0=1
	// set SEL0, SEL1 appropriately
	P1SEL0 |= BIT3;
	P1SEL1 &= ~BIT3;
	
	P1SEL0 |= BIT2;
	P1SEL1 &= ~BIT2;

	// CTLW0 register - release from reset state
	UCA0CTLW0 &= ~BIT0;

	// disable interrupts (transmit ready, start received, transmit empty, receive full)	
	// IE register; 
	EUSCI_A0->IE &= 0xFFF0;
	/*UCA0IE &= ~UCTXCPTIE;
	UCA0IE &= ~UCSTTIE;
	UCA0IE &= ~UCTXIE;
	UCA0IE &= ~UCRXIE;*/
}

char uart0_getchar()
{
	BYTE inChar;
	// Wait for data
	// IFG register
	/*while ((UCA0IFG & BIT0) == 0) {
		//check UCR0IFG
	}*/

	// read character and store in inChar variable
	// RXBUF register
	inChar = UCA0RXBUF;
	

	//Return the 8-bit data from the receiver 
	return(inChar);
}

void uart0_putchar(char ch)
	{
	// Wait until transmission of previous bit is complete 
	// IFG register
	while ((UCA0IFG & BIT1) == 0) {
		//check UCT0IFG
	}
	
	// send ch character to uart
	// TXBUF register 
	UCA0TXBUF = ch;
}

void uart0_put(char *ptr_str)
{
	while(*ptr_str != 0)
		uart0_putchar(*ptr_str++);
}
BOOLEAN uart0_dataAvailable()
{
	BOOLEAN go = FALSE;
	// if a character is available, set go = TRUE
	if ((UCA0IFG & BIT0) != 0){
		go = TRUE;
	}
	return go;
}
void uart2_init()
{
	uint32_t N;
	//Set the UART to RESET state (set bit0 of EUSCI_A0->CTLW0 register to '1'
	UCA2CTLW0 |= BIT0;

	// bit15=0,      no parity bits
	// bit14=x,      not used when parity is disabled
	// bit13=0,      LSB first
	// bit12=0,      8-bit data length
	// bit11=0,      1 stop bit
	// bits10-8=000, asynchronous UART mode
	// bits7-6=11,   clock source to SMCLK
	// bit5=0,       reject erroneous characters and do not set flag
	// bit4=0,       do not set flag for break characters
	// bit3=0,       not dormant
	// bit2=0,       transmit data, not address (not used here)
	// bit1=0,       do not transmit break (not used here)
	// bit0=1,       hold logic in reset state while configuring

	// set CTLW0 - hold logic and configure clock source to SMCLK
	UCA2CTLW0 |= BIT7;
	UCA2CTLW0 |= BIT6;

	// baud rate
	// N = clock/baud rate = clock_speed/BAUD_RATE
	// set BRW register
	N = SystemCoreClock / BAUD_RATE;
	UCA2BRW = N;

	// clear first and second modulation stage bit fields
	// MCTLW register;  
	UCA2MCTLW &= 0x000F; // clear bits 15 - 4
	

	// P3.3 = TxD
	// P3.2 = RxD
	// we will be using P3.2, P3.3 for RX and TX but not in I/O mode, so we set Port3 SEL1=0 and SEL0=1
	// set SEL0, SEL1 appropriately
	P3SEL0 |= BIT3;
	P3SEL1 &= ~BIT3;
	
	P3SEL0 |= BIT2;
	P3SEL1 &= ~BIT2;

	// CTLW0 register - release from reset state
	UCA2CTLW0 &= ~BIT0;

	// disable interrupts (transmit ready, start received, transmit empty, receive full)	
	// IE register; 
	UCA2IE &= 0xFFF0;
	/*UCA0IE &= ~UCTXCPTIE;
	UCA0IE &= ~UCSTTIE;
	UCA0IE &= ~UCTXIE;
	UCA0IE &= ~UCRXIE;*/
}
char uart2_getchar()
{
	BYTE inChar;
	// Wait for data
	// IFG register
	/*while ((UCA2IFG & BIT0) == 0) {
		//check UCR0IFG
	}*/

	// read character and store in inChar variable
	// RXBUF register
	inChar = UCA2RXBUF;
	

	//Return the 8-bit data from the receiver 
	return(inChar);
}
void uart2_putchar(char ch)
{
	// Wait until transmission of previous bit is complete 
	// IFG register
	while ((UCA2IFG & BIT1) == 0) {
		//check UCT2IFG
	}
	
	// send ch character to uart
	// TXBUF register 
	UCA2TXBUF = ch;
}
void uart2_put(char *ptr_str)
{
	while(*ptr_str != 0)
		uart2_putchar(*ptr_str++);
}
BOOLEAN uart2_dataAvailable()
{
	// if a character is available, return TRUE
	if (EUSCI_A2->IFG & BIT0) {
		return TRUE;
	}
	return FALSE;
}
