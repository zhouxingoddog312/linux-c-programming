#include <iostream>
#include <string>
#include "Sales_data.h"
int main()
{
	Sales_data temp1,temp2;
	double price=0;
	std::cin>>temp1.Bookno>>temp1.sold>>price;
	temp1.revenue=temp1.sold*price;
	price=0;
	std::cin>>temp2.Bookno>>temp2.sold>>price;
	temp2.revenue=temp2.sold*price;
	if(temp1.Bookno==temp2.Bookno)
		std::cout<<temp1.Bookno<<" "<<temp1.sold+temp2.sold<<" "<<temp1.revenue+temp2.revenue<<std::endl;
	else
		std::cerr<<"not the same isbn";
	return 0;
}
