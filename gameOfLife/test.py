#!/usr/bin/python
import curses
def main():
    stdscr = curses.initscr()
    curses.noecho()
    curses.raw()
    stdscr.keypad(1)
    curses.curs_set(0)
    curses.mousemask(1)

    GL = {}
    GL['running'] = True
    GL['mouseClick'] = False
    while GL['running']:
        stdscr.erase()
        R, C = stdscr.getmaxyx()
        for r in range(R-1):
            for c in range(C-1):
                stdscr.addch(r,c,'*')
        stdscr.refresh()
        key = stdscr.getch()
        if key == ord('q'):
            GL['running'] = False
        elif key == curses.KEY_MOUSE:
            GL['running'] = False
            GL['mouseClicked'] = True
    
    curses.endwin()
    print("Exited properly")

try:
    main()
except:
    curses.endwin()
    print("Something was wrong.")