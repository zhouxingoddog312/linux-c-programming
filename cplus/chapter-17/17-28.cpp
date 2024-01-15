#include <iostream>
#include <random>
unsigned rad()
{
	static std::default_random_engine e;
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
