/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "stdio.h"
#include "timer.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h" 
#include "../quoridor/quoridor.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
int counter = TURN_TIME;

void TIMER0_IRQHandler (void)
{ 
	static uint8_t text_timer[3];
	//stop timer 0 and reset										
	disable_timer(0);
	reset_timer(0);
	sprintf((char *) text_timer, "%02d", counter);
	// countdown has ended. Change player turn
	if (counter == 0)
		change_turn(); 
	
	if (counter>-1)
	{
		if (counter < 6)
			GUI_Text(113, 285, (uint8_t *) text_timer, Red, White);			
		else
			GUI_Text(113, 285, (uint8_t *) text_timer, Black, White);
		//continue with the countdown
			counter--;
	}
	
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
