#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
int main(void)
{
	const char witch_one[]=" First Witch  ";
	const char witch_two[]=" Second Witch ";
	const char *scan_ptr;
	initscr();
	move(5,15);
	attron(A_BOLD);
	printw("%s","Macbetch");
	attroff(A_BOLD);
	refresh();
	sleep(2);
	move(8,15);
	attron(A_STANDOUT);
	printw("%s","Thunder and Lightning");
	attroff(A_STANDOUT);
	refresh();
	sleep(2);
	move(10,10);
	attron(A_UNDERLINE);
	printw("%s","When shall we three meet again");
	move(11,23);
	printw("%s","In thunder, lightning, or in rain ?");
	attroff(A_UNDERLINE);
	move(13,10);
	attron(A_BLINK);
	printw("%s","When the hurlyburly's done,");
	move(14,23);
	printw("%s","When the battle's lost and won.");
	attroff(A_BLINK);
	refresh();
	sleep(2);
	attron(A_DIM);
	scan_ptr=witch_one+strlen(witch_one)-1;
	while(scan_ptr!=witch_one)
	{
		move(10,10);
		insch(*scan_ptr--);
	}
	scan_ptr=witch_two+strlen(witch_two)-1;
	while(scan_ptr!=witch_two)
	{
		move(13,10);
		insch(*scan_ptr--);
	}
	attroff(A_DIM);
	refresh();
	sleep(2);
	move(LINES-1,COLS-1);
	refresh();
	sleep(1);
	endwin();
	exit(EXIT_SUCCESS);
}
