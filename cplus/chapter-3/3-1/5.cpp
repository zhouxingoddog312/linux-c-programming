#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
struct Sales_data
{
	string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data temp1,temp2;
	double price=0;
	cin>>temp1.Bookno>>temp1.sold>>price;
	temp1.revenue=temp1.sold*price;
	price=0;
	cin>>temp2.Bookno>>temp2.sold>>price;
	temp2.revenue=temp2.sold*price;
	if(temp1.Bookno==temp2.Bookno)
		cout<<temp1.Bookno<<" "<<temp1.sold+temp2.sold<<" "<<temp1.revenue+temp2.revenue<<endl;
	else
		cerr<<"not the same isbn";
	return 0;
}
