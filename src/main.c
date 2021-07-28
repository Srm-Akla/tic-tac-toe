#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

#define	WIDTH  6
#define	HEIGHT 4

int half_width = (WIDTH/2);
int half_height= (HEIGHT/2);
int matrix[3][3]={
    {1,2,3},
    {4,5,6},
    {7,8,9}
};

typedef struct _tile{
    int x, y, h, w;
    
}TILE;

void init_tile(TILE *tile, int n);
WINDOW *create_newwin(int height, int width, int starty, int startx, int n);
void create_board(WINDOW *win, int n,int matrix[3][3]);

void check_win(char **board, int n);
void movement(WINDOW *win, int x, int y);

int main(int argc, char *argv[]){
    WINDOW *win;
    TILE tile;
    char **board;
    
    int ch, n=3;
    static int score[2]={0,0};
    char player[2];

    //n = atoi(argv[1]);
    srand((unsigned) time(NULL));
    const int random = rand() % 100;
    player[0] = (random % 2 == 0) ? 'X':'O';
    player[1] = (random % 2 == 1) ? 'X':'O';
    
    board = (char**)calloc(n,sizeof(char*));
    for(int i=0;i<n;i++)
	*(board+i)=(char*)calloc(n,sizeof(char));


    initscr();			
    start_color();		
    cbreak();			
				
    noecho();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);


    keypad(stdscr, TRUE);
    attron(COLOR_PAIR(1));
    printw("Press Q to exit");
    printw(" -- ");
    printw("Press F1 to clear screen");
    refresh();
    attroff(COLOR_PAIR(1));
   
    // Initialize the window parameters
    init_tile(&tile, n);
    win = create_newwin(tile.h, tile.w, tile.y, tile.x,n);
    create_board(win,n,matrix);

    attron(COLOR_PAIR(2));
    mvprintw(tile.y-3,tile.x,"Player_%c: %d (You)", player[0], score[0]);
    mvprintw(tile.y-2,tile.x,"Player_%c: %d", player[1], score[1]);
    attroff(COLOR_PAIR(2));
    
    //create_board(n,board);
    refresh();
    while((ch = getch()) != 'q'){
    wmove(win, half_height, half_width);
	switch(ch){
	    case KEY_UP:
		wmove(win, (half_height)-=HEIGHT, half_width);
		wrefresh(win);
		break;
	    case KEY_DOWN:
		wmove(win, (half_height)+=HEIGHT, half_width);
		wrefresh(win);
		break;
	    case KEY_LEFT:
		wmove(win, (half_height), half_width-=WIDTH );
		wrefresh(win);
		break;
	    case KEY_RIGHT:
		wmove(win, (half_height), half_width+=WIDTH );
		wrefresh(win);
		break;
	    case 'e':
   		wattron(win,COLOR_PAIR(3));
		mvwprintw(win,half_height,half_width,"%c",player[1]);
		wrefresh(win);
		wattroff(win,COLOR_PAIR(3));
		break;
	    case KEY_F(1):
		wclear(win);
		wrefresh(win);
		break;
	    case ' ':
   		wattron(win,COLOR_PAIR(2));
		mvwprintw(win,half_height,half_width,"%c",player[0]);
		wrefresh(win);
		wattroff(win,COLOR_PAIR(2));
		break;
	}
    }

    endwin();  
    free(board);
    

    return 0;
}

void init_tile(TILE *tile, int n){

    tile->h=(HEIGHT*n)+1;
    tile->w=(WIDTH*n)+1;
    tile->y=(LINES - (tile->h))/2;
    tile->x=(COLS - (tile->w))/2;
}

WINDOW *create_newwin(int height, int width, int starty, int startx, int n){

    WINDOW *local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);

    for(int i=1;i<n;i++){
	mvwhline(local_win, HEIGHT*i, 1, 0, width-2); 
	mvwvline(local_win, 1,WIDTH*i, 0, height-2);
    }
    wrefresh(local_win);

    return (local_win);
}


void create_board(WINDOW *win,int n,int matrix[3][3]){
    
    for(int i=0;i<n;i++){
	for(int j=0;j<n;j++){
	    mvwprintw(win,(half_height),(half_width),"%d",matrix[i][j]);
	    (half_width)+=WIDTH;
	    wrefresh(win);
	}
	half_height+=HEIGHT;
	half_width = WIDTH/2;
    }
}

void movement(WINDOW *win, int x, int y){

}

void check_win(char **board, int n){


}
