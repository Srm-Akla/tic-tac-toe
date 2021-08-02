#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

#define	WIDTH  6
#define	HEIGHT 4

int half_width = (WIDTH/2);
int half_height= (HEIGHT/2);


typedef struct _tile{
    int x, y, h, w;
    
}TILE;

void init_tile(TILE *tile, int n);
WINDOW *create_newwin(int height, int width, int starty, int startx, int n);

//void create_board(WINDOW *win, int n,int matrix[3][3]);
void update_board(WINDOW *win, short *y, short *x, char **board, char player);
bool check_win(char **board, int n);
void game_over(int x);

int main(int argc, char *argv[]){
    WINDOW *win;
    TILE tile;
    char **board;
    short x,y;
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
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);


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
    //create_board(win,n,matrix);

    attron(COLOR_PAIR(2));
    mvprintw(tile.y-3,tile.x,"Player_%c: %d (You)", player[0], score[0]);
    mvprintw(tile.y-2,tile.x,"Player_%c: %d", player[1], score[1]);
    attroff(COLOR_PAIR(2));
    /*
    attron(COLOR_PAIR(4));
    game_over(tile.x);
    attroff(COLOR_PAIR(4));
    */
    //create_board(n,board);
    refresh();
    wmove(win, half_height,half_width);
    wrefresh(win);
    while((ch = getch()) != 'q'){
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
		//waddch(win, player[1]);
		mvwprintw(win,half_height,half_width,"%c",player[1]);
		update_board(win, &y, &x, board, player[1]);
		wrefresh(win);
		wattroff(win,COLOR_PAIR(3));
		break;
	    case KEY_F(1):
		wclear(win);
		wrefresh(win);
		break;
	    case ' ':
   		wattron(win,COLOR_PAIR(2));
		//waddch(win, player[0]);
		mvwprintw(win,half_height,half_width,"%c",player[0]);
		wrefresh(win);
		wattroff(win,COLOR_PAIR(2));

		update_board(win, &y, &x, board, player[0]);
		if(check_win(board,n)==true){
		    attron(COLOR_PAIR(4));
		    game_over(tile.x);
		    attroff(COLOR_PAIR(4));
		}
		wrefresh(win);
		break;
	}
    }

    endwin();  
    
    for(int i=0;i<n;i++){
	for(int j=0;j<n;j++){
	    printf("%c ",*(*(board+i)+j));
	}
	printf("\n");
    }

    free(board);
    //printf("%d -- %d \n", y, x);
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


void update_board(WINDOW *win, short *y, short *x, char **board, char player){

    getyx(win, *(y), *(x));
    //printw("%d -- %d \n", x,y);
    
    switch(*y){
	case 2:
	    switch(*x){
		case 4:
		    *(*(board+0)+0)=player;
		    break;
		case 10:
		    *(*(board+0)+1)=player;
		    break;
		case 16:
		    *(*(board+0)+2)=player;
		    break;
	    }
		    break;
	case 6:
	    switch(*x){
		case 4:
		    *(*(board+1)+0)=player;
		    break;
		case 10:
		    *(*(board+1)+1)=player;
		    break;
		case 16:
		    *(*(board+1)+2)=player;
		    break;
	    }
		    break;
	case 10:
	    switch(*x){
		case 4:
		    *(*(board+2)+0)=player;
		    break;
		case 10:
		    *(*(board+2)+1)=player;
		    break;
		case 16:
		    *(*(board+2)+2)=player;
		    break;
	    }
		    break;
    }
    


}

bool check_win(char **board, int n){

    if(*(*(board+0)+0)==*(*(board+0)+1) && *(*(board+0)+0)==*(*(board+0)+2)){

	return true;
    }
    return false;
}

void game_over(int x){

    short y = LINES/3;
    mvprintw(y,x+strlen("Game Over!")/2,"Game Over!");
    getch();
    endwin();
    exit(EXIT_SUCCESS);
}
