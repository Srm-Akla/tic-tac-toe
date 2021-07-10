#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

void start_tui();

int main(){

    time_t t;
    srand((unsigned) time(&t));

    int player = rand() % 2;
    char human = (player == 1) ? 'X' : 'O';
    char computer = (player != 1) ? 'X' : 'O';
    char board[3][3];

    
   // for(int i=0;i<3;i++){
   //     for(int j=0;j<3;j++){
   //         scanf("%s",&board[i][j]);
   //     }
   // }

   // for(int i=0;i<3;i++){
   //     for(int j=0;j<3;j++){
   //         printf("%c ",board[i][j]);
   //     }
   //     printf("\n");
   // }

    printf("%d -- %c -- %c\n", player,human,computer);

    start_tui();
    return 0;
}

void start_tui(){

    int row,col;
    char ch[10];

    initscr();			/* Start curses mode 		  */
    raw();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr,row,col);

    move(row-2,col/10);
    getstr(ch);
    mvprintw(row/2,(col-strlen(ch))/2,"You typed %s",ch);
    mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
    

    refresh();			/* Print it on to the real screen */
    getch();			/* Wait for user input */
    endwin();			/* End curses mode		  */

}
