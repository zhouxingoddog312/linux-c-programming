#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
int main(void)
{
	initscr();
	move(5,15);
	printw("%s","Hello World!");
	box(stdscr,ACS_VLINE,ACS_HLINE);
	for(int i=0;i<3;i++)
	{
		beep();
		sleep(1);
	}
	refresh();
	sleep(2);
	endwin();
	exit(EXIT_SUCCESS);
}
