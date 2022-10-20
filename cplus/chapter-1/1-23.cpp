#include <iostream>
#include "Sales_item.h"
int main()
{
	Sales_item current_item,next_item;
	if(std::cin>>current_item)
	{
		int cnt=1;
		while(std::cin>>next_item)
		{
			if(current_item.isbn()==next_item.isbn())
			{
				current_item+=next_item;
				cnt++;
			}
			else
			{
				std::cout<<current_item<<" ocurrs "<<cnt<<" times."<<std::endl;
				current_item=next_item;
				cnt=1;
			}
		}
		std::cout<<current_item<<" ocurrs "<<cnt<<" times."<<std::endl;
	}
	return 0;
}
