#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
struct Sales_data
{
	string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data temp;
	double price=0.0;
	while(cin>>temp.Bookno)
	{
		cin>>temp.sold>>price;
		temp.revenue=temp.sold*price;
		cout<<temp.Bookno<<" "<<temp.sold<<" "<<temp.revenue<<endl;
		price=0;
	}
	return 0;
}
