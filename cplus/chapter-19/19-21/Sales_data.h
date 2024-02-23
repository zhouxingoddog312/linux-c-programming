#include <iostream>
#include <string>
#include <stdexcept>
class isbn_mismatch: public std::logic_error
{
public:
	explicit isbn_mismatch(const std::string &s):std::logic_error(s) {}
	isbn_mismatch(const std::string &s,const std::string &lhs,const std::string &rhs):std::logic_error(s),left(lhs),right(rhs) {}
	const std::string left,right;
};
class Sales_data
{
	friend std::istream & operator>>(std::istream &,Sales_data &);
	friend std::ostream & operator<<(std::ostream &,const Sales_data &);
	friend Sales_data operator+(const Sales_data &,const Sales_data &);
	public:
		std::string isbn() const {return bookNo;}
		Sales_data()=default;
		Sales_data(const std::string &s):bookNo(s) {}
		Sales_data(const std::string &s,unsigned n,double p):bookNo(s),units_sold(n),revenue(n*p) {}
		Sales_data & operator+=(const Sales_data &);
		operator std::string() const {return bookNo;}
		operator double() const {return revenue;}
		double avg_price() const;
	private:
		std::string bookNo;
		unsigned units_sold=0;
		double revenue=0.0;
};
std::istream & operator>>(std::istream &,Sales_data &);
std::ostream & operator<<(std::ostream &,const Sales_data &);
Sales_data operator+(const Sales_data &,const Sales_data &);
bool compareIsbn(const Sales_data &lhs,const Sales_data &rhs);
