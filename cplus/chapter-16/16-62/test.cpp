#include <iostream>
#include <unordered_set>
#include "Sales_data.h"
int main(void)
{
	std::unordered_multiset<Sales_data> SDset;
	Sales_data a{"100",2,20},b{"101",3,25},c{"100",2,20};
	SDset.insert(a);
	SDset.insert(b);
	SDset.insert(c);
	for(const auto& setit:SDset)
		std::cout<<setit<<std::endl;
	return 0;
}
