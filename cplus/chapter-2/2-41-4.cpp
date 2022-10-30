#include <iostream>
#include <string>
struct Sales_data
{
	std::string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data total,temp;
	double price=0.0;
	if(std::cin>>total.Bookno)
	{
		std::cin>>total.sold>>price;
		total.revenue=total.sold*price;
		while(std::cin>>temp.Bookno)
		{
			std::cin>>temp.sold>>price;
			temp.revenue=temp.sold*price;
			price=0;
			if(total.Bookno==temp.Bookno)
			{
				total.sold+=temp.sold;
				total.revenue+=temp.revenue;
			}
			else
			{
				std::cout<<total.Bookno<<" "<<total.sold<<" "<<total.revenue<<std::endl;
				total.Bookno=temp.Bookno;
				total.sold=temp.sold;
				total.revenue=temp.revenue;
			}
		}
		std::cout<<total.Bookno<<" "<<total.sold<<" "<<total.revenue<<std::endl;
	}
	else
	{
		std::cerr<<"no data."<<std::endl;
		return -1;
	}
	return 0;
}
