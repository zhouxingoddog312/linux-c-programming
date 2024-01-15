#include <iostream>
#include <random>
#include <ctime>
unsigned rad(int sd=time(0))
{
	static std::default_random_engine e(sd);
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}
int main(void)
{
	for(size_t i=0;i<100;++i)
		std::cout<<rad()<<" ";
	std::cout<<std::endl;
	return 0;
}
