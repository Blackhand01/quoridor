
#ifndef QUORIDOR_LAB_H_
#define QUORIDOR_LAB_H_

#include <stdint.h>
#include <stdlib.h>
#include "stdbool.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "../GLCD/GLCD.h"
#include "game_map.h"
#include "../joystick/joystick.h"

#define NORTH 0x3
#define SOUTH 0x1
#define EAST	0x2
#define WEST	0x4

#define NUM_WALLS	8
#define MAP_DIM 15

#define TIMER0 0x00098968		// 1s in emulation, 25 ms emulation -> 1s || (1000 ms x 25k Hz = 1s -> 0x17D7840)
#define TIMER1 0x001312D0		// 2s in emulation
#define RIT 	 0x000F4240		// 200ms 0x001E8480, 100ms 0x000F4240

#define	PLY0_COLOR Blue
#define	PLY1_COLOR Green

#define	WALLUNSEL_COLOR Magenta
#define	WALL_COLOR Red

#define TURN_TIME 20

#define VISITED false
#define UNVISITED true
	
typedef enum {
	PLY0 = (uint8_t) '0',
	PLY1 = (uint8_t) '1',
	FREE = (uint8_t) 'O',
	OBST = (uint8_t) 'X',
	EXIT = (uint8_t) 'E'
} slot_t;


typedef struct {
	uint8_t row;
	uint8_t col;
} pos_t;


typedef struct {
	pos_t new_pos;							// colonna e riga
	uint8_t playerID;						// player 0 e player 1
	unsigned playerMove		: 4; 	// 0 -> move, 1 -> wall
	unsigned orientation	: 4;	// 0 -> vertical (default), 1 -> horizontal
} player_t;


void start_game(void);
void change_mode(void);
void change_orientation(void);
void change_turn(void);
void game_init(void);
void player_init(player_t *p, char playerID, int row, int col, unsigned playerMove, unsigned orientation);
void player_wall_place(uint8_t dir);
bool player_place(uint8_t dir);
bool wall_place(uint8_t dir);
bool get_new_pos(uint8_t dir, int row, int col);
bool canReachDestination(char plyId);
bool findPath(slot_t game_grid_copy[MAP_DIM][MAP_DIM], int row, int col, char plyId);

#endif
