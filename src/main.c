#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

typedef struct _tile{
    int x, y, h, w;
    
}TILE;

void init_tile(TILE *tile, int n);
void create_board(TILE *tile, int n);

int main(int argc, char *argv[]){

    TILE tile;
    int ch, n;
    int board[3][3];

    int player = rand() % 2;
    char human = (player == 1) ? 'X' : 'O';
    char computer = (player != 1) ? 'X' : 'O';
    
    if(argc <2){
	printf("Type here!");
	exit(99);
    }
    n = atoi(argv[1]);

    initscr();			
    start_color();		
    cbreak();			
				
    keypad(stdscr, TRUE);	
    noecho();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);


    attron(COLOR_PAIR(1));
    printw("Press F1 to exit");
    refresh();
    attroff(COLOR_PAIR(1));
   
    /* Initialize the window parameters */
    init_tile(&tile, n);
    create_board(&tile, n);
    refresh();

   // attron(COLOR_PAIR(2));
   // move(win.starty+1,win.startx+1);
   // attroff(COLOR_PAIR(2));
    while((ch = getch()) != KEY_F(1)){
	switch(ch){	
	    case KEY_RIGHT:
		move(4,3);
		clrtoeol();
		mvprintw(3,3,"Space works");
		break;
	    case KEY_LEFT:
		move(3,3);
		clrtoeol();
		mvprintw(4,3,"Space works");
		break;
	}
    }
    
    endwin();			/* End curses mode		  */
    return 0;
}

void init_tile(TILE *tile, int n){

    tile->h=6;
    tile->w=8;
    tile->y=(LINES - (tile->h)*n)/2;
    tile->x=(COLS - (tile->w)*n)/2;

}

void create_board(TILE *tile,int n){
    
    WINDOW *local_win;
    local_win = newwin(tile->h, tile->w, tile->y, tile->x);
    refresh();
    box(local_win,0 ,0);
    wrefresh(local_win);		

    for(int i=0;i<n;i++){
	for(int j=0;j<n;j++){
    
	    mvprintw((tile->y+tile->h)+i,(tile->x+tile->w)+j,"%d -- %d", i, j);
    
	}
	printf("\n");
    }
}
