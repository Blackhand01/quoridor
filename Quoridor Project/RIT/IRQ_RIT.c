/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../quoridor/quoridor.h"
#include "stdbool.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:	None
**
******************************************************************************/
#define IS_JOYSEL_PRESSED() ((LPC_GPIO1->FIOPIN & (1 << 25)) == 0)		// la funzione è true se il bit 25 è 0 (premuto)
#define IS_JOYUP_PRESSED() 	((LPC_GPIO1->FIOPIN & (1 << 29)) == 0)
#define IS_JOYDW_PRESSED() 	((LPC_GPIO1->FIOPIN & (1 << 26)) == 0)
#define IS_JOYLT_PRESSED() 	((LPC_GPIO1->FIOPIN & (1 << 27)) == 0)
#define IS_JOYRT_PRESSED() 	((LPC_GPIO1->FIOPIN & (1 << 28)) == 0)

extern int lock;
extern int game_mode;
bool is_sel_pressed = false;
// Funzione per ottenere l'input dal joystick
void get_joystick_input(uint8_t *direction) {
	is_sel_pressed = IS_JOYSEL_PRESSED();
  	*direction = ' ';
	if (IS_JOYSEL_PRESSED() && game_mode == 1) 		// Se sono in modalità giocatore e ho premuto sel
	{
		lock=1; 
		if (IS_JOYUP_PRESSED()) 
			*direction = NORTH;
		else if (IS_JOYDW_PRESSED()) 
			*direction = SOUTH;
		else if (IS_JOYRT_PRESSED())
			*direction = EAST;
		else if (IS_JOYLT_PRESSED()) 
			*direction = WEST;
	}
	else if (game_mode == 2) 		// Se sono in modalità muro e non ho premuto sel
	{
		lock=2;
		if (IS_JOYUP_PRESSED()) 
			*direction = NORTH;
		else if (IS_JOYDW_PRESSED()) 
			*direction = SOUTH;
		else if (IS_JOYRT_PRESSED())
			*direction = EAST;
		else if (IS_JOYLT_PRESSED()) 
			*direction = WEST;
	}		// Se sono in modalità muro e ho premuto sel
}



void RIT_IRQHandler(void) {
	uint8_t direction;
	enable_timer(0);				//da 20 a 0 sec
	get_joystick_input(&direction);
	if(is_sel_pressed && game_mode == 2)		// Se sono in modalità muro e ho premuto sel
		lock=1;
 	switch (direction) {
			case NORTH:
					player_wall_place(NORTH);
					break;
			case SOUTH:
					player_wall_place(SOUTH);
					break;
			case WEST:
					player_wall_place(WEST);
					break;
			case EAST:
					player_wall_place(EAST);
					break;
			default:
			{
				if(game_mode == 2 && lock == 1)
					player_wall_place(direction);
			}
	}
	if(game_mode == 1)
		lock = 0;
	disable_RIT();
	reset_RIT();
	enable_RIT();
	joystick_init();
	LPC_RIT->RICTRL |= 0x1;		/* clear interrupt flag */
  return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
