[toc]
### 14.1
- 不同点：重载运算符至少有一个类类型的运算对象。重载运算符实际上是具有特殊名字的函数，所以它无法保留内置运算符的求值顺序或短路求值属性。重载运算符有可能被定义成与内置运算符不一样的含义。
- 相同点：重载运算符与内置运算符在运算对象数量、优先级和结合律等方面保持一致。
### 14.2
<a id="1">Sales_data.h</a>
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
### 14.6
[见14.2](#1)
### 14.7
==String.h==
```
#ifndef _sTRING_H
#define _sTRING_H
#include <iostream>
#include <utility>
class String
{
	friend std::istream & operator>>(std::istream &in,String &str);
	friend std::ostream & operator<<(std::ostream &out,const String &str);
	public:
		String():head(nullptr),tail(nullptr),cap(nullptr) {}
		String(const char *);
		String(const String &);
		String(String &&str) noexcept :head(str.head),tail(str.tail),cap(str.cap) {str.head=str.tail=str.cap=nullptr;std::cout<<"This is move constructor."<<std::endl;}
		String & operator=(const String &);
		String & operator=(String &&);
		String operator+(const String &);
		~String() {free();}

		size_t size() const {return tail-head;}
		size_t capacity() const {return cap-head;}
		bool empty() const {return (head==tail)?true:false;}
		char * begin() const {return head;}
		char * end() const {return tail;}
	private:
		char *head;
		char *tail;
		char *cap;
		static std::allocator<char> alloc;
		void free();

		std::pair<char *,char *> alloc_n_copy(const char *,const char *);
		void chk_n_alloc(size_t n) {if(n+size()>capacity()) reallocate(n);}
		void reallocate(size_t n);
};
std::istream & operator>>(std::istream &in,String &str);
std::ostream & operator<<(std::ostream &out,const String &str);
#endif
```
==String.cpp==
```
#include <memory>
#include <algorithm>
#include <cstring>
#include <string>
#include "String.h"

String::String(const char *str)
{
	size_t n=strlen(str);
	std::pair<char *,char *> newdata=alloc_n_copy(str,str+n);
	head=newdata.first;
	tail=cap=newdata.second;
}
String::String(const String &s)
{
	std::cout<<"This is copy constructor."<<std::endl;
	std::pair<char *,char *> newdata=alloc_n_copy(s.begin(),s.end());
	head=newdata.first;
	tail=cap=newdata.second;
}
String & String::operator=(const String &rhs)
{
	std::cout<<"This is copy assignment operator."<<std::endl;
	std::pair<char *,char *> newdata=alloc_n_copy(rhs.begin(),rhs.end());
	free();
	head=newdata.first;
	tail=cap=newdata.second;
	return *this;
}
String & String::operator=(String &&rhs)
{
	std::cout<<"This is move assignment operator."<<std::endl;
	if(this!=&rhs)
	{
		free();
		head=rhs.head;
		tail=rhs.tail;
		cap=rhs.cap;
		rhs.head=rhs.tail=rhs.cap=nullptr;
	}
	return *this;
}
String String::operator+(const String &rhs)
{
	String tmp(*this);
	size_t n=rhs.size();
	tmp.chk_n_alloc(n);
	char *dest=tmp.tail;
	char *src=rhs.begin();
	for(size_t i=0;i!=6;++i)
		alloc.construct(dest++,*src++);
	tmp.tail=dest;
	return tmp;
}

std::allocator<char> String::alloc;
void String::free()
{
	if(head)
	{
		std::for_each(begin(),end(),[](char &c) {alloc.destroy(&c);});
		alloc.deallocate(head,cap-head);
	}
}
std::pair<char *,char *> String::alloc_n_copy(const char *b,const char *e)
{
	char *newdata=alloc.allocate(e-b);
	return {newdata,std::uninitialized_copy(b,e,newdata)};
}
void String::reallocate(size_t n)
{
	size_t newcap=(size()>n?size()*2:n*2);
	char *newdata=alloc.allocate(newcap);
	char *dest=newdata;
	char *src=head;
	for(size_t i=0;i!=size();++i)
		alloc.construct(dest++,std::move(*src++));
	free();
	head=newdata;
	tail=dest;
	cap=head+newcap;
}
std::istream & operator>>(std::istream &in,String &str)
{
	std::string tmp;
	in>>tmp;
	String Stmp(tmp.c_str());
	str=Stmp;
	return in;
}
std::ostream & operator<<(std::ostream &out,const String &str)
{
	std::for_each(str.begin(),str.end(),[&out](const char &c)->void {out<<c;});
	return out;
}
```
### 14.8
<a id="2">Employee.h</a>
```
#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H
#include <iostream>
class Employee
{
	friend std::ostream & operator<<(std::ostream &,const Employee &);
	friend std::istream & operator>>(std::istream &,Employee &);
	public:
		Employee()=default;
		Employee(std::string s):name(s){}
		Employee(std::string s,unsigned int i,double j,unsigned int k):name(s),Age(i),salary(j),Phone_Number(k){}
	private:
		std::string name;
		unsigned int Age=0;
		double salary=0;
		unsigned int Phone_Number=0;
};
std::ostream & operator<<(std::ostream &,const Employee &);
std::istream & operator>>(std::istream &,Employee &);
#endif
```
==Employee.cpp==
```
#include "Employee.h"
std::ostream & operator<<(std::ostream &os,const Employee &src)
{
	os<<src.name<<" "<<src.Age<<" "<<src.salary<<" "<<src.Phone_Number;
	return os;
}
std::istream & operator>>(std::istream &is,Employee &src)
{
	is>>src.name>>src.Age>>src.salary>>src.Phone_Number;
	if(!is)
		src=Employee();
	return is;
}
```
### 14.9
[见14.2](#1)
### 14.10
1. 输入正确，可以得到输入中的正确数据
2. 输入错误，可以得到默认值的Sales_data对象
### 14.11
此重载的输入运算符没有判断输入失败的情况，在输入失败时，bookNo、units_sold、price都可能是非法数据，由此得到非法的Sales_data对象。这个输入运算符如果仍然给定上个练习的输入，那么第一个输入仍将得到合法的对象，而第二个输入会得到非法的对象。
### 14.12
[见14.8](#2)
### 14.13
对于Sales_data类，其它的算术运算符没有明确的意义
### 14.14
因为operator+本来就是返回的值，所以使用operator+=并不会有性能上的损失，同时具有较高的可读性.
### 14.15
Employee类的信息是雇员的名字、年纪、收入、电话，算术运算符对其没有明确的意义，故不应该含有其他算术运算符。
### 14.16

### 14.17

### 14.18

### 14.19
Employee类可以按雇员的名字、年龄、收入、电话号码比较，所以不存在一种逻辑可靠的<定义，所以它不应该含有关系运算符。
### 14.20
[见14.2](#1)
### 14.21
我感觉缺点不明显，性能上并没有什么损失，可读性？
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
```
### 14.22

### 14.23

### 14.24

### 14.25
需要定义一个运算对象为string的赋值运算符，可以直接为雇员的名字赋值.
