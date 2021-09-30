#include <unistd.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define PW_LEN 256
#define NAME_LEN 256
int main(void)
{
	char name[NAME_LEN];
	char passwd[PW_LEN];
	const char *real_passwd="xyzzy";
	initscr();
	move(5,10);
	printw("%s","Please login:");
	move(7,10);
	printw("%s","User name: ");
	getnstr(name,NAME_LEN);
	move(8,10);
	printw("%s","Password: ");
	cbreak();
	noecho();
	memset(passwd,'\0',sizeof(passwd));
	for(int i=0;i<PW_LEN;i++)
	{
		passwd[i]=getch();
		if(passwd[i]=='\n')
			break;
		//move(8,20+i);
		addch('*');
		refresh();
	}
	echo();
	nocbreak();
	move(11,10);
	if(strncmp(real_passwd,passwd,strlen(real_passwd))==0)
		printw("%s","Correct");
	else
		printw("%s","Wrong");
	printw("%s"," password");
	refresh();
	sleep(2);
	endwin();
	exit(EXIT_SUCCESS);
}
