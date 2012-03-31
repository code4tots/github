#include<stdlib.h>
#include<ncurses.h>

// Model
char map[100][100];
int posr, posc; // position.
int dirr, dirc; // direction.
int R, C; // Rows and Columns in Model.
int running;
void moveModel(int dr, int dc){
	if (posr+dr < 0 || posr+dr >= R || posc+dc < 0 || posc+dc >= C){
		// do nothing.
	}
	else {
		map[posr][posc] = 0;
		posr += dr;
		posc += dc;
		map[posr][posc] = 1;
	}
}
void wrappedMoveModel(char c){
	char dr[256];
	char dc[256];
	dr['a'] = 0; dc['a'] = -1;
	dr['s'] = 1; dc['s'] = 0;
	dr['w'] = -1; dc['w'] = 0;
	dr['d'] = 0; dc['d'] = 1;
	moveModel(dr[c],dc[c]);
}
void clearModel(){ int r, c; for (r = 0; r < 100; r++) { for (c = 0; c < 100; c++) { map[r][c] = 0; } } }
void initModel(int r, int c){ R = r; C = c; clearModel(); posr = R/2; posc = C/2; map[posr][posc] = 1;}
void dirModel(int r, int c) { dirr = r; dirc = c; }
void incModel(){
	map[posr][posc] = 0;
	posr += dirr;
	posc += dirc;
	// check whether the game has ended.
	if (posr < 0 || posr >= R || posc < 0 || posc >= C){
		running = FALSE;
	}
	else {
		map[posr][posc] = 1;
	}
}

// Controller/View (declarations)
void run();


// main ------------
int main(int argc, char* argv[]){
	initModel(10,10);
	run();
	return 0;
}

// Controller/View (implementations)
// All ncurses logic.
void run(){
	// convenient iterator variables.
	int r, c, maxR, maxC, lowR, lowC;
	char toDraw;

	initscr();
	noecho();
	raw();
	curs_set(0);
	
	char key;
	running = TRUE;
	while (running){
		// draw model.
		
		// clear screen
		erase();
		
		// calculate boundaries
		getmaxyx(stdscr, maxR,maxC);
		lowR = (maxR - R - 2) / 2;
		lowC = (maxC - C - 2) / 2;
		
		// draw boundaries
		for (c = lowC; c < lowC + C; c++){
			mvaddch(lowR-1,c, '&');
			mvaddch(lowR+R,c, '&');
		}
		for (r = lowR; r < lowR + R; r++){
			mvaddch(r,lowC-1, '&');
			mvaddch(r,lowC+C, '&');
		}
		
		// draw map
		for (r = 0; r < R; r++){
			for (c = 0; c < C; c++){
				switch(map[r][c]){
					case 0:
						toDraw = ' ';
						break;
					case 1:
						toDraw = '*';
						break;
						
					default:
						toDraw = '?';
				}
				
				mvaddch(r + lowR,c + lowC, toDraw);
			}
		}
		// make sure everything shows up on the screen
		refresh();
		
		// handle input
		switch(key = getch()){
			// -- exit --
			case 3: // ctrl-c
				running = FALSE;
				break;
			// -- movement --
			case 'a':
			case 's':
			case 'd':
			case 'w':
				wrappedMoveModel(key);
				break;
		}
	}
	
	endwin();
}
