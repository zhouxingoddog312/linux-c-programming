#include <iostream>
#include <random>
#include <ctime>
unsigned rad(unsigned sd=time(0),unsigned min=0,unsigned max=9)
{
	static std::default_random_engine e(sd);
	static std::uniform_int_distribution<unsigned> u(min,max);
	return u(e);
}
int main(void)
{
	for(size_t i=0;i<100;++i)
		std::cout<<rad(1,1,10)<<" ";
	std::cout<<std::endl;
	return 0;
}
