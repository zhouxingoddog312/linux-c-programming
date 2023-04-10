#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
class Sales_data;
istream &read(istream &is,Sales_data &item);
class Sales_data
{
friend Sales_data add(const Sales_data &lhs,const Sales_data &rhs);
friend ostream &print(ostream &os,Sales_data &item);
friend istream &read(istream &is,Sales_data &item);
private:
	string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	double avg_price() const;
public:
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	Sales_data():Sales_data("",0,0){}
	Sales_data(istream &is):Sales_data(){read(is,*this);}
	Sales_data(const string &s):Sales_data(s,0,0){}
	Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold{n},revenue{n*p}{}
};
inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream &os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
bool compareIsbn(Sales_data &s1,Sales_data &s2)
{
	return s1.isbn()<s2.isbn();
}
int main(void)
{
	Sales_data tmp;
	vector<Sales_data> Sales_data_vec;
	while(read(cin,tmp))
		Sales_data_vec.push_back(tmp);
	sort(Sales_data_vec.begin(),Sales_data_vec.end(),[](Sales_data &d1,Sales_data&d2)->bool{return d1.isbn()<d2.isbn();});
	for(auto &t:Sales_data_vec)
	{
		print(cout,t);
		cout<<endl;
	}
	return 0;
}
