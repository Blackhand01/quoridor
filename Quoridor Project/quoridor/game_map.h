
#ifndef MAP_H_
#define MAP_H_

#define LCD_MAP_START_X			06
#define LCD_MAP_START_Y			45

#define LCD_P1_START_X			10
#define LCD_P1_START_Y			270
#define LCD_P1_LENGTH				45
#define LCD_P1_WIDTH				75
#define LCD_P1_END_X				(LCD_P1_START_X + LCD_P1_WIDTH)
#define LCD_P1_END_Y				(LCD_P1_START_Y + LCD_P1_LENGTH)

#define LCD_TIMER_START_X		95
#define LCD_TIMER_START_Y		270
#define LCD_TIMER_LENGTH		45
#define LCD_TIMER_WIDTH			55
#define LCD_TIMER_END_X			(LCD_TIMER_START_X + LCD_TIMER_WIDTH)
#define LCD_TIMER_END_Y			(LCD_TIMER_START_Y + LCD_TIMER_LENGTH)


#define LCD_P2_START_X			160
#define LCD_P2_START_Y			270
#define LCD_P2_LENGTH				45
#define LCD_P2_WIDTH				75
#define LCD_P2_END_X				(LCD_P2_START_X + LCD_P2_WIDTH)
#define LCD_P2_END_Y				(LCD_P2_START_Y + LCD_P2_LENGTH)


#define MAX_SCREEN_X				240
#define MAX_SCREEN_Y				320
#define GRID_SIZE						MAX_SCREEN_X
#define GRID_SIZE						MAX_SCREEN_X
#define CELL_SIZE						28 
#define	SPACING 						7 
#define PLAYER_SIZE 				10 
#define WALL_WIDTH 					SPACING
#define WALL_LENGHT 				63
/*
#define WITHIN_INTERVAL(val, a, b) (((val) >= (a)) && ((val) <= (b)))

#define LCD_POSCOL(col) (LCD_MAP_START_X + ((col)*15))
#define LCD_POSROW(row) (LCD_MAP_START_Y + ((row)*15))

#define LCD_GAMEROW(cgame) (LCD_POSROW(cgame.robot.curr_pos.row - 1))
#define LCD_GAMECOL(cgame) (LCD_POSCOL(cgame.robot.curr_pos.col - 1))

#define LCD_MAP_BKCOLOR		Black*/
#endif

