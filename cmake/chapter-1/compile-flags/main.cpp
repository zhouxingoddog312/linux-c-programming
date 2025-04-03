#include <iostream>
int main(void)
{
	std::cout<<"Hello compile flags!"<<std::endl;
#ifdef EX2
	std::cout<<"Hello compile flag EX2."<<std::endl;
#elif	defined(EX3)
	std::cout<<"Hello compile flag EX3."<<std::endl;
#else
	std::cout<<"There is no additional flags."<<std::endl;
#endif
	return 0;
}
