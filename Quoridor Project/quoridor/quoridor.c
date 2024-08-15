	#include "quoridor.h"

	/** Game modes:
	 * 0 -> waiting for Int0
	 * 1 -> player move Mode
	 * 2 -> wall insertion Mode
	 */
	int game_mode = 0;			
	int player_turn = 0;
	int orientation = 0;
	/** Lock modes:
	 * 0 -> free
	 * 1 -> block, move place
	 * 2 -> wall not place
	 */
	int lock = 0;
	extern int counter;
	player_t p0, p1;
	int curPos_row, curPos_col;
	int pasPos_row, pasPos_col;
	int p_walls[2] = {NUM_WALLS, NUM_WALLS};

	bool visited[MAP_DIM][MAP_DIM];  // Matrice per tenere traccia delle posizioni visitate

slot_t game_grid[MAP_DIM][MAP_DIM] = {
//j:	0			1			2			3			4			5			6			7			8			9			10		11		12		13		14		// i:
		{OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST}, //  0
		{OBST, EXIT, FREE, EXIT, FREE, EXIT, FREE, PLY0, FREE, EXIT, FREE, EXIT, FREE, EXIT, OBST}, //  1
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, //  2
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, //  3
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, //  4
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, //  5
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, //  6
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, //  7
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, //  8
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, //  9
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, // 10
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, // 11
		{OBST, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE, OBST}, // 12
		{OBST, EXIT, FREE, EXIT, FREE, EXIT, FREE, PLY1, FREE, EXIT, FREE, EXIT, FREE, EXIT, OBST}, // 13
		{OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST, OBST}	// 14
	};



// Schermata di inizio + creazione player
void start_game(){
		LCD_Clear(White);				
		//LCD_DrawInterface();
		LCD_DrawGrid();
		game_init();
}

void reset_globals()
{
	pasPos_row = 7;	//variabili utili per il gioco
	pasPos_col = 6;
	curPos_row = -1;
	curPos_col = -1;
}

/* Inizializzo il campo di gioco */
void game_init() {
	reset_globals();
	
	player_init(&p0, '0', 1,  7, 0, 0);
	player_init(&p1, '1', 13, 7, 0, 0);
	player_wall_place(' ');
	game_mode = 1;															// player mode

}
/* Crea il giocatore */
void player_init(player_t *p, char playerID, int row, int col, unsigned playerMove, unsigned orientation) {
	p->playerID = playerID;
	p->new_pos.row = row;
	p->new_pos.col = col;
	p->playerMove = playerMove;
	p->orientation = orientation;
}

/* se sono in wall mode vado in player mode */
void change_mode(){
	player_t *current_player = (player_turn == 0) ? &p0 : &p1;
	
	if(lock != 1)
	{		
		if(game_mode == 2) 
		{
			if(lock == 2)
				LCD_DrawWall(pasPos_col/2, pasPos_row/2, White);
			game_mode = 1;		
			current_player -> playerMove = 0x1;
		}		
		else
		{
			game_mode = 2;
			current_player -> playerMove = 0x0;
		}
	}
}


/* Rotate player/wall position of 90 degree */
void change_orientation(){
	player_t *current_player  = (player_turn == 0) ? &p0 : &p1;
	if(lock == 2)
		LCD_DrawWall(pasPos_col/2, pasPos_row/2, White);
	if(lock != 1 && game_mode == 2)
	{
		if(orientation == 1)
		{
			pasPos_row -= (uint8_t) 1;
			pasPos_col += (uint8_t) 1;
			orientation = 0;		
			current_player -> orientation = 0x0;	// 0 -> vertical (default)
		}		
		else
		{
			pasPos_row += (uint8_t) 1;
			pasPos_col -= (uint8_t) 1;
			orientation = 1;			
			current_player -> orientation = 0x1;	// 1 -> horizontal
		}
	}
}


/* Turn passes to the other player */
void change_turn(){
	if(game_mode>0)
	{
		if(lock == 2)
			LCD_DrawWall(pasPos_col/2, pasPos_row/2, White);
		game_mode = 0;		
		lock = 0;
		player_turn = (player_turn == 0) ? 1 : 0;
		game_mode = 1;	
		orientation = 0;
		
		reset_globals();
		
		counter = TURN_TIME;
		enable_timer(0);
	}			
}


//aggiorna posizione
bool get_new_pos(uint8_t dir, int row, int col){
	player_t *current_player  = (player_turn == 0) ? &p0 : &p1;
	
	switch(dir)
	{
		case NORTH:
			if(game_grid[row-1][col] == OBST)
				return false;
			row = row-2;
		break;
		
		case SOUTH:
			if(game_grid[row+1][col] == OBST)
				return false;
			row = row+2;
		break;
		
		case EAST:
			if(game_grid[row][col+1] == OBST)
				return false;
			col = col+2;
		break;
		
		case WEST:
			if(game_grid[row][col-1] == OBST)
				return false;
			col = col-2;
		break;
	}
	if(game_mode == 1 && (col<1 || col>(MAP_DIM-2) || row<1 || row>(MAP_DIM-2)))
		 return false;
	if(game_mode == 2 && orientation == 0 && (col<1 || col>(MAP_DIM-2) || row<1 || row>(MAP_DIM-4)))
		 return false;
	if(game_mode == 2 && orientation == 1 && (col<1 || col>(MAP_DIM-4) || row<1 || row>(MAP_DIM-2)))
		 return false;
	current_player->new_pos.row = (uint8_t) row;
	current_player->new_pos.col = (uint8_t) col;
	return true;
}								


/* Cambia posizione: piazza giocatori e muri */
void player_wall_place(uint8_t dir){
	uint16_t color, col, row, k;
	player_t *current_player;
	uint8_t text_wall[3];
	
 	current_player = (player_turn == 0) ? &p0 : &p1;

  switch(game_mode)
	{
		case 0:
		{
			col = p0.new_pos.col/2;
			row = p0.new_pos.row/2;
			LCD_DrawPlayer(col, row, PLY0_COLOR);
			col = p1.new_pos.col/2;
			row = p1.new_pos.row/2;
			LCD_DrawPlayer(col, row, PLY1_COLOR);
		}break;
		
		case 1: 
		{
     	if(player_place(dir))
			{
				row = curPos_row/2;
				col = curPos_col/2;
				LCD_DrawPlayer(col, row, White);	//sbianchetto old pos
				
				color = (current_player->playerID == '1') ? PLY1_COLOR : PLY0_COLOR;
				row = current_player->new_pos.row/2;
				col = current_player->new_pos.col/2;
				LCD_DrawPlayer(col, row, color);	//coloro new pos
				change_turn();
			}
		}break;
		
		case 2:
		{
			if(wall_place(dir))
			{
				if(!canReachDestination('0') || !canReachDestination('1'))
				{// allora ripristino 
					current_player->new_pos.row = (uint8_t) pasPos_row;
					current_player->new_pos.col = (uint8_t) pasPos_col;
					row = pasPos_row;
					col = pasPos_col; 
					if(orientation == 0)
					{
						for(k=0; k<3; k++, row++)						// occupo la griglia
							if(game_grid[row][col] == OBST)
								game_grid[row][col] = FREE;
					}
					else
					{
						for(k=0; k<3; k++, col++)						// occupo la griglia
							if(game_grid[row][col] == OBST)
								game_grid[row][col] = FREE;
					}
					return;
				}
				color = (lock == 1) ? WALL_COLOR : WALLUNSEL_COLOR;
				if(game_grid[pasPos_row][pasPos_col] != OBST)
				{
					row = pasPos_row/2;
					col = pasPos_col/2;
					LCD_DrawWall(col, row, White);					//sbianchetto old pos
				}
				row = current_player->new_pos.row/2;
				col = current_player->new_pos.col/2;
				LCD_DrawWall(col, row, color);					//coloro new pos
				
				pasPos_row = (int) current_player->new_pos.row;		//aggiorno vecchie posizione con le nuove
				pasPos_col = (int) current_player->new_pos.col;
				if(lock == 1)
				{
					col = (player_turn == 0) ? 43 : 193;
					p_walls[player_turn]--;
					sprintf((char *) text_wall, "%d", p_walls[player_turn]);
					GUI_Text(col, 295, (uint8_t *) text_wall, Black, White);
					change_turn();
				}
			}
		}
	}
}


/* gestione del player */
bool player_place(uint8_t dir){
	int trovato, i, j;
	char gridElem, plyId;
	player_t *current_player;
	pos_t newPos;
	
	current_player = (player_turn == 0) ? &p0 : &p1;
	plyId = current_player->playerID;

	// ricerca player
	for(trovato=0, i=0; i<MAP_DIM && trovato == 0; i++)
		for(j=0; j<MAP_DIM && trovato == 0; j++)
			if(game_grid[i][j] == plyId)
			{
				trovato = 1;	// giocatore trovato, salvo la sua posizione (src)
				curPos_row = i;
				curPos_col = j;
			}
 	if(trovato == 0)	//se non trovo il giocatore, annullo l'operazione
		return false;
	
	if(!get_new_pos(dir, curPos_row, curPos_col))	// vado nella posizione diretta dal joystick (salto)
		return false;		
	
	newPos.row = current_player->new_pos.row;					// posizioni aggiornate
	newPos.col = current_player->new_pos.col;
	gridElem = game_grid[newPos.row][newPos.col];			// elem nella posizione della destinazione
  
	// se la posizione appartiene all'altro giocatore, lo scavalco
    if(gridElem == PLY0 || gridElem == PLY1)
	{
		if(!get_new_pos(dir, newPos.row, newPos.col))
			return false;
		newPos.row = current_player->new_pos.row;				// posizioni aggiornate
		newPos.col = current_player->new_pos.col;
		gridElem = game_grid[newPos.row][newPos.col];		// elem nella posizione della destinazione
	}
	
	
	// Cambio di posizione
 	if(gridElem == EXIT)
	{
		if( (newPos.row == 1 && plyId==PLY1) || (newPos.row == (MAP_DIM-2) && plyId==PLY0)) //qualcuno ha vinto
		{
			if(newPos.row == (MAP_DIM-2) && plyId==PLY0) 
			GUI_Text(5, 250, (uint8_t *) "!!! HA VINTO PLAYER 0 !!!", PLY0_COLOR, White);
			if(newPos.row == 1 && plyId==PLY1) 
				GUI_Text(5, 250, (uint8_t *) "!!! HA VINTO PLAYER 1 !!!", PLY1_COLOR, White);
			game_grid[newPos.row][newPos.col] = plyId;					
			game_mode=0;
			disable_timer(0);
			return true;
		}
		else	//nessuno ha vinto, il player è nella sua zona
		{
			if( (curPos_row == 1 && plyId==PLY0) || (curPos_row == (MAP_DIM-2) && plyId==PLY1)) 
				game_grid[curPos_row][curPos_col] = EXIT;		// era una EXIT position per l'avversario (ripristino della src)
			else
				game_grid[curPos_row][curPos_col] = FREE;		// era una FREE position (ripristino della src)
			game_grid[newPos.row][newPos.col] = plyId;		// mi sposto la destinazione
			return true;
		}
		return false;
	}
	else 
	if(gridElem == FREE)
	{
		if( (curPos_row == 1 && plyId==PLY0) || (curPos_row == (MAP_DIM-2) && plyId==PLY1)) 
			game_grid[curPos_row][curPos_col] = EXIT;		// era una EXIT position per l'avversario (ripristino della src)
		else
			game_grid[curPos_row][curPos_col] = FREE;		// era una FREE position (ripristino della src)
		game_grid[newPos.row][newPos.col] = plyId;		// mi sposto la destinazione
		return true;
	}
	return false;	
}


/* gestione del muro */
bool wall_place(uint8_t dir){
	int col, row, k;
	char gridElem;
	player_t *current_player;
  current_player = (player_turn == 0) ? &p0 : &p1;
	
	// se non ho abbastanza muri
	if(p_walls[player_turn]<1)
		return false;

	// vado nella posizione diretta dal joystick
	if(!get_new_pos(dir, pasPos_row, pasPos_col))
		return false;

	// posizioni aggiornate (variabili di comodo)
	row = (int) current_player->new_pos.row;					
 	col = (int) current_player->new_pos.col;
	
 	switch(orientation)
	{
		case 0:	// vertical
		{
			//nel caso ci sia un ostacolo lo salto
			for(k=0; k<3; k++, row++)
			{
				gridElem = game_grid[row][col];			// cosa c'è attualmente nella posizione in cui voglio andare
 				if(row > (MAP_DIM-2))									// se sono in exit zone o fuori gioco non va bene
					return false;
				if(gridElem != FREE)
				{
					
					if(!get_new_pos(dir, (int) current_player->new_pos.row, (int) current_player->new_pos.col))	// vado nella posizione diretta dal joystick (salto)
						return false;							
					row = (uint8_t) current_player->new_pos.row;	// posizioni aggiornate
					k=0;
				}
			}
			current_player -> new_pos.row = (uint8_t) (row - 3);			// ripristino posizione di partenza del muro
      row = (int) current_player->new_pos.row;
			col = (int) current_player->new_pos.col;			
			
			if(lock == 1)
			{
				for(k=0; k<3; k++, row++)						// occupo la griglia
					if(game_grid[row][col] == FREE)
						game_grid[row][col] = OBST;
			}
			return true;
		}break;
		
		case 1:	// horizontal
		{
			//nel caso ci sia un ostacolo lo salto
			for(k=0; k<3; k++, col++)
			{
				gridElem = game_grid[row][col];			// cosa c'è attualmente nella posizione in cui voglio andare
 				if(col > (MAP_DIM-2))									// se sono in exit zone o fuori gioco non va bene
					return false;
				if(gridElem != FREE)
				{
					if(!get_new_pos(dir, (int) current_player->new_pos.row, (int) current_player->new_pos.col))	// vado nella posizione diretta dal joystick (salto)
						return false;							
					col = (uint8_t) current_player->new_pos.col;	// posizioni aggiornate
					k=0;
				}
			}
			current_player -> new_pos.col = (uint8_t) (col - 3);			// ripristino posizione di partenza del muro
			col = (int) current_player->new_pos.col;
			row = (int) current_player->new_pos.row;	

			if(lock == 1)
			{
				for(k=0; k<3; k++, col++)						// occupo la griglia
					if(game_grid[row][col] == FREE)
						game_grid[row][col] = OBST;
					//else return false
			}			
			return true;
		}
	}
	return false;
}


bool canReachDestination(char plyId) {
	slot_t game_grid_copy[MAP_DIM][MAP_DIM];
	int trovato, i, j, endRow, startRow, startCol;
    for(trovato=0, i=0; i<MAP_DIM && trovato == 0; i++)
			for(j=0; j<MAP_DIM && trovato == 0; j++)
				if(game_grid[i][j] == plyId)
				{
					trovato = 1;	// giocatore trovato, salvo la sua posizione (src)
					startRow = i;
					startCol = j;
				}
		for ( i = 0; i < MAP_DIM; i++) {
        for ( j = 0; j < MAP_DIM; j++) {
          visited[i][j] = UNVISITED;
					game_grid_copy[i][j] = game_grid[i][j];
        }
    }
    return findPath(game_grid_copy, startRow, startCol, plyId);
}
                     
bool findPath(slot_t game_grid_copy[MAP_DIM][MAP_DIM], int row, int col, char plyId) {
		if (visited[row][col] == VISITED) {
					return false;
			}

    // Contrassegna il nodo come visitato
    visited[row][col] = VISITED;
    // Verifica se il giocatore ha raggiunto la destinazione
    if ((plyId == '0' && row == MAP_DIM - 2) || (plyId == '1' && row == 1)) {
        return true;
    }

    // Verifica e muovi di 1 posizione a destra
    if (col < MAP_DIM - 1 && game_grid_copy[row][col + 1] != OBST && game_grid_copy[row][col + 2] != plyId) {
        game_grid_copy[row][col + 2] = plyId;
        if (findPath(game_grid_copy, row, col + 2, plyId)) {
            return true;
        }
    }

    // Verifica e muovi di 1 posizione a sinistra
    if (col >= 1 && game_grid_copy[row][col - 1] != OBST && game_grid_copy[row][col - 2] != plyId) {
        game_grid_copy[row][col - 2] = plyId;
        if (findPath(game_grid_copy, row, col - 2, plyId)) {
            return true;
        }
    }

    // Verifica e muovi di 1 posizione in basso
    if (row < MAP_DIM - 1 && game_grid_copy[row + 1][col] != OBST && game_grid_copy[row + 2][col] != plyId) {
        game_grid_copy[row + 2][col] = plyId;
        if (findPath(game_grid_copy, row + 2, col, plyId)) {
            return true;
        }
    }
		
		if (row >= 1 && game_grid_copy[row - 1][col] != OBST && game_grid_copy[row - 2][col] != plyId) {
    game_grid_copy[row - 2][col] = plyId;
    if (findPath(game_grid_copy, row - 2, col, plyId)) {
        return true;
    }
}
		
		// Ripristina il nodo come non visitato quando nessun percorso è trovato
    visited[row][col] = UNVISITED;
		
    // Nessun percorso trovato
    return false;

}
