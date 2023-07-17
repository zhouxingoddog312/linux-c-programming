[toc]
### 14.1
- 不同点：重载运算符至少有一个类类型的运算对象。重载运算符实际上是具有特殊名字的函数，所以它无法保留内置运算符的求值顺序或短路求值属性。重载运算符有可能被定义成与内置运算符不一样的含义。
- 相同点：重载运算符与内置运算符在运算对象数量、优先级和结合律等方面保持一致。
### 14.2
==Sales_data.h==
```
#include <iostream>
#include <string>
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
	private:
		std::string bookNo;
		unsigned units_sold=0;
		double revenue=0.0;
		double avg_price() const;
};
std::istream & operator>>(std::istream &,Sales_data &);
std::ostream & operator<<(std::ostream &,const Sales_data &);
Sales_data operator+(const Sales_data &,const Sales_data &);
```
==Sales_data.cpp==
```
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
```
### 14.3
1. `"cobble"=="stone"`比较的两个数据都是const char *类型，使用了内置运算符；
2. `svec1[0]==svec2[0]`比较的两个数据都是string &，使用了string类型重载的==；
3. `svec1==svec2`比较的两个数据都是vector，使用了vector类型重载的==；
4. `svec1[0]=="stone"`中"stone"将会转换为string，使用了string类型重载的==；
### 14.4
$\%$非成员函数
$\%=$成员函数
$++$成员函数
$->$成员函数
$<<$非成员函数
$\&\&$非成员函数
$==$非成员函数
$()$成员函数
### 14.5
联系7.40中，编写的是Employee的框架，建议为其重载输入、输出运算符。

