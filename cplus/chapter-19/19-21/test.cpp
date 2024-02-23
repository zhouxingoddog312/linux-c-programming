#include <iostream>
#include <string>
#include "token.h"
int main(void)
{
	Token t;
	t=1;
	std::cout<<t<<std::endl;
	t='c';
	std::cout<<t<<std::endl;
	t=1.314;
	std::cout<<t<<std::endl;
	t="hello";
	std::cout<<t<<std::endl;
	t=Sales_data("10212x",3,24);
	std::cout<<t<<std::endl;
	return 0;
}
