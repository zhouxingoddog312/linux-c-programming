#include <iostream>
#include "Screen.h"
int main(void)
{
	Screen scr(5,6,'*');
	scr.move(2,3);
	auto pc=Screen::data();
	std::cout<<scr.*pc<<std::endl;
	return 0;
}
