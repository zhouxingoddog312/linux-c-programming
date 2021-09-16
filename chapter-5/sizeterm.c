#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
int main(void)
{
	int nrows,ncolums;
	setupterm(NULL,fileno(stdout),(int *)0);
	nrows=tigetnum("lines");
	ncolums=tigetnum("cols");
	printf("This terminal has %d columns and %d rows.\n",ncolums,nrows);
	exit(0);
}
