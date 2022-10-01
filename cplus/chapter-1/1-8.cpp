#include <iostream>
int main()
{
//只有第三行的错误的
	std::cout<<"/*";
	std::cout<<"*/";
	//std::cout<</*"*/"*/;
	std::cout<</**/"*/";//上一行的更正
	std::cout<</* "*/" /* "/*"  */;
	return 0;
}
