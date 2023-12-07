#include <iostream>
#include <string>
#include <functional>
class Sales_data
{
	friend class std::hash<Sales_data>;
	friend std::istream & operator>>(std::istream &,Sales_data &);
	friend std::ostream & operator<<(std::ostream &,const Sales_data &);
	friend Sales_data operator+(const Sales_data &,const Sales_data &);
	friend bool operator==(const Sales_data &,const Sales_data &);
	friend bool operator!=(const Sales_data &,const Sales_data &);
	public:
		std::string isbn() const {return bookNo;}
		Sales_data()=default;
		Sales_data(const std::string &s):bookNo(s) {}
		Sales_data(const std::string &s,unsigned n,double p):bookNo(s),units_sold(n),revenue(n*p) {}
		Sales_data & operator+=(const Sales_data &);
		operator std::string() const {return bookNo;}
		operator double() const {return revenue;}
	private:
		std::string bookNo;
		unsigned units_sold=0;
		double revenue=0.0;
		double avg_price() const;
};
std::istream & operator>>(std::istream &,Sales_data &);
std::ostream & operator<<(std::ostream &,const Sales_data &);
Sales_data operator+(const Sales_data &,const Sales_data &);
bool operator==(const Sales_data &,const Sales_data &);
bool operator!=(const Sales_data &,const Sales_data &);
namespace std
{
	template <> class hash<Sales_data>
	{
		public:
			typedef size_t result_type;
			typedef Sales_data argument_type;
			size_t operator()(const Sales_data &s) const;
	};
}
