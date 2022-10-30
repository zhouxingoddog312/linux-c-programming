#include <iostream>
#include <string>
#include "Sales_data.h"
int main()
{
	Sales_data temp;
	double price=0.0;
	while(std::cin>>temp.Bookno)
	{
		std::cin>>temp.sold>>price;
		temp.revenue=temp.sold*price;
		std::cout<<temp.Bookno<<" "<<temp.sold<<" "<<temp.revenue<<std::endl;
		price=0;
	}
	return 0;
}
