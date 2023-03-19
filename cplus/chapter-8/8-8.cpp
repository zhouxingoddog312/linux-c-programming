#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Sales_data
{
	string bookNo;
	unsigned units_sold{0};
	double revenue{0.0};
};
int main(int argc,char *argv[])
{
	struct Sales_data  total,trans;
	double price;
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2],ofstream::app|ofstream::out);

	if(ifst>>total.bookNo)
	{
		ifst>>total.units_sold>>price;
		total.revenue=total.units_sold*price;
		while(ifst>>trans.bookNo)
		{
			ifst>>trans.units_sold>>price;
			trans.revenue=trans.units_sold*price;
			if(total.bookNo==trans.bookNo)
			{
				total.units_sold+=trans.units_sold;
				total.revenue+=trans.revenue;
			}
			else
			{
				ofst<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
				total.bookNo=trans.bookNo;
				total.units_sold=trans.units_sold;
				total.revenue=trans.revenue;
			}
		}
		ofst<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
	}
	else
	{
		cerr<<"No data?"<<endl;
		return -1;
	}
	return 0;
}
