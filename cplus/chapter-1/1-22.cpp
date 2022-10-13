#include <iostream>
#include "Sales_item.h"
int main()
{
	Sales_item result,tmp;
	std::cin>>result;
	while(std::cin>>tmp)
		result+=tmp;
	std::cout<<result<<std::endl;
	return 0;
}
