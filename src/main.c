#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>


typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;

void create_box(WIN *p_win, bool flag);

int main(int argc, char *argv[]){
    WIN win;
    int ch;

    int player = rand() % 2;
    char human = (player == 1) ? 'X' : 'O';
    char computer = (player != 1) ? 'X' : 'O';

    initscr();			
    start_color();		
    cbreak();			
				
    keypad(stdscr, TRUE);	
    noecho();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    /* Initialize the window parameters */

    attron(COLOR_PAIR(1));
    printw("Press F1 to exit");
    refresh();
    attroff(COLOR_PAIR(1));
    
    attron(COLOR_PAIR(2));
    create_box(&win, TRUE);
    move(win.starty+1,win.startx+1);
    attroff(COLOR_PAIR(2));
    while((ch = getch()) != KEY_F(1)){	
	switch(ch){	
	    case KEY_LEFT:
		move(win.starty,(win.startx-=16));
		break;
	    case KEY_RIGHT:
		move(win.starty,(win.startx+=16));
		break;
	    case KEY_UP:
		move((win.starty-=4),win.startx);
		break;
	    case KEY_DOWN:
		move((win.starty+=4),win.startx);
		break;	
	    case KEY_F(2):
		mvprintw(10,10,"Helloworld");
		break;
	    }
    }
    endwin();			/* End curses mode		  */
    return 0;
}


void create_box(WIN *p_win, bool flag){	
    int i, j;
    int x, y, w, h;

    p_win->height = 9;
    p_win->width = 45;
    p_win->starty = (LINES - p_win->height)/2;	
    p_win->startx = (COLS - p_win->width)/2;

    p_win->border.ls = '|';
    p_win->border.rs = '|';
    p_win->border.ts = '-';
    p_win->border.bs = '-';
    p_win->border.tl = '+';
    p_win->border.tr = '+';
    p_win->border.bl = '+';
    p_win->border.br = '+';

    x = p_win->startx;
    y = p_win->starty;
    w = p_win->width;
    h = p_win->height;

    if(flag == TRUE){	
	mvaddch(y, x, p_win->border.tl);
	mvaddch(y, x + w, p_win->border.tr);
	mvaddch(y + h, x, p_win->border.bl);
	mvaddch(y + h, x + w, p_win->border.br);
	mvhline(y, x + 1, p_win->border.ts, w - 1);
	mvhline(y + h, x + 1, p_win->border.bs, w - 1);
	
	//Inside Lines
	mvhline(y + 3, x + 1, p_win->border.ts, w - 1);
	mvhline(y + 6, x + 1, p_win->border.ts, w - 1);
	mvvline(y + 1, x + 15, p_win->border.ls, h - 1);
	mvvline(y + 1, x + 30, p_win->border.ls, h - 1);
	
	mvvline(y + 1, x, p_win->border.ls, h - 1);
	mvvline(y + 1, x + w, p_win->border.rs, h - 1);

    }else{
	for(j = y; j <= y + h; ++j)
	    for(i = x; i <= x + w; ++i)
		mvaddch(j, i, ' ');
    }			    
    refresh();

}
