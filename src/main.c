#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define	WIDTH  8
#define	HEIGHT 6

typedef struct _tile{
    int x, y, h, w;
    int state;
    
}TILE;

void init_tile(TILE *tile, int n);
WINDOW *create_newwin(int height, int width, int starty, int startx, int n);
void create_board(int n,int **board);

int main(int argc, char *argv[]){
    WINDOW *win;
    TILE tile;
    int **board;
    
    int ch, n;
    n = atoi(argv[1]);
    /*srand((unsigned) time(NULL));
    int player = rand() % 100;
    bool playerX = (player % 2 == 0) ? true : false;
    bool playerO = (player % 2 == 1) ? true : false;*/
    
    board=(int **)calloc(n,sizeof(int*));
    for(int i=0;i<n;i++){
	*(board+i)=(int *)calloc(n,sizeof(int));
    }
    
    
    initscr();			
    start_color();		
    raw();			
				
    noecho();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);


    keypad(stdscr, TRUE);
    attron(COLOR_PAIR(1));
    printw("Press Q to exit");
    refresh();
    attroff(COLOR_PAIR(1));
   
    // Initialize the window parameters
    init_tile(&tile, n);
    win = create_newwin(tile.h, tile.w, tile.y, tile.x,n);

   // attron(COLOR_PAIR(2));
   // move(win.starty+1,win.startx+1);
   // attroff(COLOR_PAIR(2));
    wmove(win, tile.y, tile.x);
    while((ch = getch()) != 'q'){
	switch(ch){
	    case KEY_LEFT:
		wmove(win, tile.y, tile.x--);
		wrefresh(win);
		break;
	    case KEY_RIGHT:
		wmove(win, tile.y, tile.x++);
		wrefresh(win);
		break;
	    case KEY_DOWN:
   		wattron(win,COLOR_PAIR(2));
		mvwprintw(win,2,4,"#");
		wrefresh(win);
		wattroff(win,COLOR_PAIR(2));
		break;
	}
    }
    
    endwin();  
    return 0;
}

void init_tile(TILE *tile, int n){

    tile->h=(HEIGHT*n)+1;
    tile->w=(WIDTH*n)+1;
    tile->y=(LINES - (tile->h))/2;
    tile->x=(COLS - (tile->w))/2;
    tile->state=(-1);
}

WINDOW *create_newwin(int height, int width, int starty, int startx, int n){

    WINDOW *local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);

    for(int i=1;i<n;i++){
	int newX, newY;
	mvwhline(local_win, i*i, 1, 0, width-2); 
	mvwvline(local_win, 1, i*i, 0, height-2);
    }
    wrefresh(local_win);

    return (local_win);
}


void create_board(int n,int **board){
    
    if(n<3){
	printf("Argument is too small \n");
	exit(1);
    }
    for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
	    printf("%d ", *(*(board+i)+j));
	}
	printf("\n");
    }

}
