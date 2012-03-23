/*
hanoi.c
3.21.2012
tower of hanoi demo using ncurses.
*/
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>

// Model.
// N -> the number of disks there are.
// disk[i] -> tower the (i+1)th largest disk is currently residing.
// reset -> reset disk and N;
#define MAX_N 20
int N;
int running = FALSE;
char srcTower;
char disk[MAX_N];
int towerError = FALSE;
void selectTower(char tower);
void moveToTower(char tower);
void reset(int n);

// Controller/View
void run();
void draw();


// main
int main(int argc, char* argv[]){
    
    if (argc < 2){
        printf("usage: %s [height of tower]\n", argv[0]);
    }
    else {
        reset(atoi(argv[1]));
        run();
    }
    return 0;
}

// implementations.
void run(){
    int i;

    // ncurses initializations.
    initscr();
    noecho();
    //cbreak();
    raw();
    keypad(stdscr, TRUE);
    
    running = TRUE;
    while (running){
        draw();
        int curChar;
        
        switch(curChar = getch()){
        // -- exit --
        case 'q':
            running = FALSE;
            break;
        // -- selections --
        case '-':
            selectTower(-1);
            break;
        case '0':
        case '1':
        case '2':
            if (srcTower == -1){
                selectTower(curChar - '0');
            }
            else {
                moveToTower(curChar - '0');
            }
            break;
        }
    }
    endwin();
}

void drawRow(int r, int c, int n, char cc){
    int i;
    move(r,c);
    for (i = 0; i < n; i++){ addch(cc); }
    // clean up remnants of possible larger disk.
    for (i = n; i < N; i++){ addch(' '); }
}
void drawTower(int r, int c, int tower){
    int i;
    int ri = 0;
    // bottom row.
    drawRow(r, c, N, '-');
    
    for (i = 0; i < N; i++) {
        if (disk[i] == tower){
            drawRow(r - ri - 1, c, N-i,'o');
            ri++;
        }
    }
    
    // clean up remnants of last tower that might
    // still be remaining.
    for (; ri < N; ri++){
        drawRow(r - ri - 1, c, N, ' ');
    }
    
}
void draw(){
    int r, c, i, j, maxR, maxC, bottomR, leftC;
    getmaxyx(stdscr,maxR,maxC);
    bottomR = (maxR + N) / 2;
    leftC = (maxC - (3 * (N+1)) )/ 2;
    
    mvprintw(bottomR - N - 3, leftC, "Press q to exit\n");
    mvprintw(bottomR - N - 2, leftC, "Towers are numbered 0, 1, 2\n");
    for (c = 0; c < 3; c++) {
        drawTower(bottomR, leftC + (N+1) * c, c);
        
        char stringBuffer[20];
        sprintf(stringBuffer, "%d", c);
        
        mvprintw(bottomR+1, leftC + (N+1) * c + (N / 2) - 1, stringBuffer);
    }
    
    if (towerError){
        mvprintw(bottomR+4, leftC, "You tried to move a larger disk on top of a larger disk\n");
        towerError = FALSE;
    }
    else if (srcTower == -1){
        mvprintw(bottomR+4, leftC, "No towers are selected\n");
    }
    else {
        mvprintw(bottomR+4, leftC, "Tower %d selected\n", srcTower);
    }
    
    refresh();
}

void selectTower(char tower){
    srcTower = tower;
}
void moveToTower(char tower){
    if (srcTower != -1 && srcTower != tower) {
        char diskIndex;
        for (diskIndex = N-1; diskIndex >= 0; diskIndex--){
            if (disk[diskIndex] == srcTower){
                disk[diskIndex] = tower;
                break;
            }
            // If we hit a tower disk before we hit a srcTower disk,
            // then we would have to put a larger disk on top
            // of the smaller disk, breaking the rules.
            else if (disk[diskIndex] == tower){
                towerError = TRUE;
                //printf("error, tried to put larger disk at tower %d, on top of smaller disk (%d) at tower %d.\n", srcTower, diskIndex, tower);
                break;
            }
        }
        srcTower = -1;
    }
}
void reset(int n) {
    int i;
    srcTower = -1;
    for (i = 0; i < MAX_N; i++) disk[i] = 0;
    N = n;
}
#undef MAX_N