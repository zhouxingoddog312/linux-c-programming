#include <iostream>
#include <string>
using namespace std;
struct Sales_data;
istream &read(istream &is,Sales_data &item);
struct Sales_data
{
	string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	double avg_price() const;
	Sales_data()=default;
	Sales_data(istream &is){read(is,*this);}
	Sales_data(const string &s):bookNo(s){}
	Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold{n},revenue{n*p}{}
};
double Sales_data::avg_price() const
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
int main(void)
{
	Sales_data a;
	print(cout,a)<<endl;
	Sales_data b("1992");
	print(cout,b)<<endl;
	Sales_data c{"1992",1,20};
	print(cout,c)<<endl;
	Sales_data d{cin};
	print(cout,d)<<endl;
	return 0;
}
