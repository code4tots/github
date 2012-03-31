#include<ncurses.h>

int main(int argc, char* argv[]){
	initscr();
	raw();
	noecho();
	keypad(stdscr,TRUE);
	
	int running = TRUE;
	char key;
	while (running){
		switch(key = getch()){
			case 'q': // q for quit.
			case 3:	// Ctrl-C
				running = FALSE;
				break;
			default:
				printw("%c %d\n", key, key);
				break;
		}
	}
	
	
	endwin();
	return 0;
}
