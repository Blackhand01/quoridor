#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"
#include "../timer/timer.h"
#include "../GLCD/GLCD.h"
#include "../quoridor/quoridor.h" 

/** Game modes:
 * 0 -> wait mode
 * 1 -> player move mode
 * 2 -> wall insertion mode
 * 3 -> rotate position of 90 degree
 */
extern int game_mode;							
extern int lock;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	if(game_mode==0)
	{
		start_game();	
		disable_timer(0);
		enable_RIT();	
	}
	NVIC_DisableIRQ(EINT0_IRQn);
	//LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	if(game_mode > 0 && lock != 1)
		change_mode();
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	if(game_mode == 2 && lock != 1)
		change_orientation();									
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */  
}


