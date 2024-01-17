#include <iostream>
#include <iomanip>
#include <cmath>
int main(void)
{
	int i=19;
	int a=-19;
	double b=sqrt(2);
	bool c=true;
	std::cout<<std::boolalpha<<c<<std::noboolalpha<<std::endl;
	std::cout<<std::showbase<<std::hex<<i<<std::noshowbase<<std::dec<<std::endl;
	std::cout<<std::setprecision(12)<<std::scientific<<std::uppercase<<b<<std::endl;
	std::cout<<std::setw(15)<<std::internal<<a<<std::ends<<'\n';
	return 0;
}
