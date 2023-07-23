#include <iostream>
#include <string>
struct func
{
	std::string operator()()
	{
		std::string tmp;
		getline(std::cin,tmp);
		return tmp;
	}
};
int main(void)
{
	func f;
	std::cout<<f()<<std::endl;
	return 0;
}
