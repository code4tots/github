/*
3.20.2012

Rewrite of demo2.c under my bitbucket project.

Just for record: http://aix1.uottawa.ca/~jkhoury/game.html  

*/

#include<stdio.h>
#include<ncurses.h>

// Model
int N;
char lights[100][100];
void toggle(int ri, int ci, int r, int c); // toggle light at (ri,ci)
// main UI loop
void run();

// main
int main(int argc, char* argv[]){
    // iterator variables.
    int i, j;

    if (argc < 2){
        printf("usage: %s [N]\n", argv[0]);
    }
    else {
        N = atoi(argv[1]);
        
        // initialize model.
        for (i = 0; i < 100; i++){  
            for (j = 0; j < 100; j++){
                lights[i][j] = 'o';
            }
        }
        
        // start the main UI loop.
        run();
    }
    return 0;
}


// implementations 
void run(){
    // iterator variables.
    int r, c, ri, ci;
    
    // Initialize ncurses
    initscr();
    
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    // View variables.
    int mRow, mCol; getmaxyx(stdscr,mRow,mCol);
    int bRow, bCol;
    bRow = (mRow - N) / 2;
    bCol = (mCol - N) / 2;
    
    // Draw for the first time.
    for (ri = 0; ri < N; ri++){
        r = ri + bRow;
        for (ci = 0; ci < N; ci++){
            c = ci + bCol;
            mvaddch(r,c, lights[ri][ci]);
        }
    }
    move(bRow,bCol);
    // make sure drawing shows up on screen.
    refresh();
    
    // main UI loop
    while (true){
        // Get some useful values
        getyx(stdscr,r,c);
        ri = r - bRow;
        ci = c - bCol;
        
        // Handle input
        switch (getch()) {
            // -- toggle --
            case ' ':
                toggle(ri,ci,r,c);
                // bounds are checked by toggle,
                toggle(ri-1,ci,r-1,c);
                toggle(ri+1,ci,r+1,c);
                toggle(ri,ci-1,r,c-1);
                toggle(ri,ci+1,r,c+1);
                move(r,c);
                break;
            // -- movement --
            // left
            case 'a':
                if (ci > 0) move(r,c-1);
                break;
            // right
            case 'd':
                if (ci < N-1) move(r,c+1);
                break;
            // up
            case 'w':
                if (ri > 0) move(r-1,c);
                break;
            // down
            case 's':
                if (ri < N-1) move(r+1, c);
                break;
        }
        
        // Make sure changes are drawn.
        refresh();
    }
}


void toggle(int ri, int ci, int r, int c){
    // do bound checking
    if ( (0 <= ri && ri < N) && (0 <= ci && ci < N) ){
    
        if (lights[ri][ci] == 'o'){
            lights[ri][ci] = 'v';
            mvaddch(r,c,lights[ri][ci]);
        }
        else {
            lights[ri][ci] = 'o';
            mvaddch(r,c,lights[ri][ci]);
        }
    }
}

