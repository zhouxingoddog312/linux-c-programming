#include <iostream>
#include <string>
using namespace std;
struct Sales_data
{
	string bookNo;
	unsigned units_sold{0};
	double revenue{0.0};
};
int main(void)
{
	struct Sales_data  total,trans;
	double price;
	if(cin>>total.bookNo)
	{
		cin>>total.units_sold>>price;
		total.revenue=total.units_sold*price;
		while(cin>>trans.bookNo)
		{
			cin>>trans.units_sold>>price;
			trans.revenue=trans.units_sold*price;
			if(total.bookNo==trans.bookNo)
			{
				total.units_sold+=trans.units_sold;
				total.revenue+=trans.revenue;
			}
			else
			{
				cout<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
				total.bookNo=trans.bookNo;
				total.units_sold=trans.units_sold;
				total.revenue=trans.revenue;
			}
		}
		cout<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
	}
	else
	{
		cerr<<"No data?"<<endl;
		return -1;
	}
	return 0;
}
