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
	if(is)
		src.revenue=src.units_sold*price;
	else
		src=Sales_data();
	return is;
}
std::ostream & operator<<(std::ostream &os,const Sales_data &src)
{
	os<<src.isbn()<<" "<<src.units_sold<<" "<<src.revenue<<" "<<src.avg_price();
	return os;
}
Sales_data & Sales_data::operator+=(const Sales_data & rhs)
{
	*this=*(this)+rhs;
	return *this;
}
Sales_data operator+(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data tmp;
	tmp.bookNo=lhs.bookNo;
	tmp.units_sold=lhs.units_sold+rhs.units_sold;
	tmp.revenue=lhs.revenue+rhs.revenue;
	return tmp;
}
bool operator==(const Sales_data &lhs,const Sales_data &rhs)
{
	return lhs.bookNo==rhs.bookNo&&lhs.units_sold==rhs.units_sold&&lhs.revenue==rhs.revenue;
}
bool operator!=(const Sales_data &lhs,const Sales_data &rhs)
{
	return !(lhs==rhs);
}
size_t std::hash<Sales_data>::operator()(const Sales_data &s) const
{
	return std::hash<std::string>()(s.bookNo)^std::hash<unsigned>()(s.units_sold)^std::hash<double>()(s.revenue);
}
