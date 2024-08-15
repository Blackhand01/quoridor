#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "button_EXINT/button.h"
#include "quoridor/quoridor.h"


#ifdef SIMULATOR
extern uint8_t ScaleFlag; /* <- ScaleFlag needs to visible in order for the emulator to find the symbol 
																(can be placed also inside system_LPC17xx.h but since it is RO, it needs more work) */
#endif

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
 
int main (void) {
	SystemInit();
	init_timer(0, TIMER0);
	init_RIT(RIT);					// 20 ms: RIT (100k Hz) used to poll the joystick
	LCD_Initialization();
	//TP_Init();
	//TouchPanel_Calibrate();								// LCD - touch panel calibration
	
	//LCD_Clear(White);											// Schermata
	GUI_Text(85,20, (uint8_t *) "Quoridor", Blue, White);
	GUI_Text(20,60, (uint8_t *) "Press 0 to start the game", Blue2, Grey);
	BUTTON_init();
	joystick_init(); 		
	LPC_SC->PCON |= 0x1;									/* Power-down	mode */
	LPC_SC->PCON &= 0xFFFFFFFD;						
	
  while (1) {                           /* Loop forever, waiting for interrupt */	
		__ASM("wfi");							
  }
}
