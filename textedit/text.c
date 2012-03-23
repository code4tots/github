/*
3.21.2012

Simple text editor using ncurses.
*/
#include<stdlib.h>
#include<string.h> // for strtok
#include<ncurses.h>
// Model.
char buffer[1000][1000] = { ' ' };
int maxR, maxC; // max row, max column.
int cursorR, cursorC; // cursor position.
int running = TRUE; // run() keeps running until FALSE
void handle(char); // modify model based on input.

// UI -- all ncurses logic contained here.
void run();


// implementations
void handle(char c){
    
}

void run(){
    // iterator variables.
    int r, c;

    // ncurses initializations
    initscr();
    
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    // enter UI loop
    while (running){
        // get relevant variables.
        getmaxyx(stdscr, maxR,maxC);
        
        // draw.
        for (r = 0; r < maxR; r++){
            for (c = 0; c < maxC; c++){
                mvaddch(r,c,buffer[r][c]);
            }
        }
        move(cursorR,cursorC);
        
        // handle input
        handle(getch());
    }
}

// main
int main(int argc, char* argv[]){
    int r, c;
    
    printf("' ' = %d\n", ' ');
    for (r = 0; r < 10; r++){
        for (c = 0; c < 10; c++){
            printf("buffer[%d][%d] = %d\n",r, c, buffer[r][c]);
        }
    }
    return 0;
}