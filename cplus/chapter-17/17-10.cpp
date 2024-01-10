#include <iostream>
#include <bitset>
int main(void)
{
	std::bitset<22> a("1000000010000100101110");
	std::cout<<a<<std::endl;
	std::bitset<22> b;
	b^=~a;
	std::cout<<b<<std::endl;
	return 0;
}
