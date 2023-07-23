#include <iostream>
struct func
{
	int operator()(int a,int b,int c) { return a>0?b:c;}
};
int main(void)
{
	func f;
	std::cout<<f(-1,2,3)<<std::endl;
	return 0;
}
