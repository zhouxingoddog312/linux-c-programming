#include "Sales_data.h"
inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
std::istream & operator>>(std::istream &is,Sales_data &src)
{
	double price=0.0;
	is>>src.bookNo>>src.units_sold>>price;
	src.revenue=src.units_sold*price;
	return is;
}
std::ostream & operator<<(std::ostream &os,const Sales_data &src)
{
	os<<src.isbn()<<" "<<src.units_sold<<" "<<src.revenue<<" "<<src.avg_price();
	return os;
}
Sales_data & Sales_data::operator+=(const Sales_data & rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
Sales_data operator+(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data tmp;
	tmp=lhs;
	tmp+=rhs;
	return tmp;
}
