[toc]
### 15.1
基类希望其派生类进行覆盖的函数，称为虚函数。任何构造函数之外的非静态函数都可以是虚函数。
### 15.2
主要区别在于派生类的成员函数及其友元是否有其访问权限，protected说明符修饰的基类成员可以被派生类成员函数及其友元访问，同时禁止派生类用户访问。而private说明符修饰的基类成员不能被派生类成员函数及其友元访问，也禁止派生类用户访问。
### 15.3
<a id="1">Quote.h</a>
```
#ifndef _QUOTE_H
#define _QUOTE_H
#include <iostream>
#include <string>
class Quote
{
	public:
		Quote()=default;
		Quote(const std::string &book,double sales_price):price(sales_price),bookNo(book) {}
		std::string isbn() const {return bookNo;}
		virtual double net_price(std::size_t n) const {return n*price;}
		virtual std::string debug() const {return "bookNo="+bookNo+"\n"+"price="+std::to_string(price);}
		virtual ~Quote()=default;
	protected:
		double price=0.0;
	private:
		std::string bookNo;
};
double print_total(std::ostream &os,const Quote &item,std::size_t n);
class Bulk_quote:public Quote
{
	public:
		Bulk_quote()=default;
		Bulk_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Quote(book,sales_price),min_qty(qty),discount(disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n>=min_qty)
				return n*(1-discount)*price;
			else
				return n*price;
		}
		virtual std::string debug() const
		{
			return Quote::debug()+"\n"+"min_qty="+std::to_string(min_qty)+"\n"+"discount="+std::to_string(discount);
		}
	private:
		std::size_t min_qty=0;
		double discount=0.0;
};


class Limit_quote:public Quote
{
	public:
		Limit_quote()=default;
		Limit_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Quote(book,sales_price),max_qty(qty),discount(disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n<=max_qty)
				return n*(1-discount)*price;
			else
				return max_qty*(1-discount)*price+(n-max_qty)*price;
		}
		virtual std::string debug() const
		{
			return Quote::debug()+"\n"+"max_qty="+std::to_string(max_qty)+"\n"+"discount="+std::to_string(discount);
		}
	private:
		std::size_t max_qty=0;
		double discount=0.0;
};
#endif
```
==Quote.cpp==
```
#include "Quote.h"
double print_total(std::ostream &os,const Quote &item,std::size_t n)
{
	double ret=item.net_price(n);
	os<<"ISBN: "<<item.isbn()<<" # sold: "<<n<<" total due: "<<ret<<std::endl;
	return ret;
}
```
### 15.4
1. 错误，一个类不能派生它本身。
2. 正确。
3. 错误，派生类的声明中不可以包含它的派生列表。
### 15.5
[见15.3](#1)
### 15.6
```
#include <iostream>
#include "Quote.h"
using namespace std;
int main(void)
{
	Quote item1("1-102-333",20);
	Bulk_quote item2("1-202-222",30,2,0.2);
	print_total(cout,item1,3);
	print_total(cout,item2,3);
	return 0;
}
```
### 15.7
```
class Limit_quote:public Quote
{
	public:
		Limit_quote()=default;
		Limit_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Quote(book,sales_price),max_qty(qty),discount(disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n<=max_qty)
				return n*(1-discount)*price;
			else
				return max_qty*(1-discount)*price+(n-max_qty)*price;
		}
	private:
		std::size_t max_qty=0;
		double discount=0.0;
};
```
### 15.8
静态类型是变量声明时的类型或表达式生成的类型，动态类型则是变量或表达式表示的内存中的对象的类型，动态类型直到运行时才可知。
### 15.9
当基类的指针或引用指向派生类对象时，就会产生静态类型与动态类型不同的情况。
```
class base{......};
class derived:public base{......};
derived objd;
base *bp=&objd;//这三种情况静态类型与动态类型不同
base &bref=objd;//这三种情况静态类型与动态类型不同
base *bp=derived *dp=&objd;//这三种情况静态类型与动态类型不同
```
### 15.10
ifstream类型派生自istream类型,因此我们可以像使用istream对象一样使用ifstream对象。在read函数中，它接受一个istream类型的引用，所以作为它派生类,ifstream也可以绑定到istream的引用上。
### 15.11
[见15.3](#1)
### 15.12
有必要，override关键字指明该函数用于覆盖掉从基类继承而来的虚函数，这种用法可以避免我们在派生类中不经意间定义了一个与继承而来的虚函数同名但形参列表不同，而导致重新声明了一个与原虚函数相互独立的的函数的情况。而final关键字指明该函数不允许后续的派生类进行覆盖。这两个关键字功能并不重复，所以可以同时声明。
### 15.13
两个print函数的目的都是打印各自的数据成员，其中派生类的print函数，函数体中会对自身版本的print函数进行调用，从而导致无限递归。派生类中的print函数应该改为`void print(ostream &os) {base::print(os);os<<" "<<i;}`。
### 15.14
1. 基类版本
2. 派生类版本
3. 基类版本
4. 基类版本
5. 基类版本
6. 派生类版本
### 15.15
<a id="2">Quote.h</a>
```
#ifndef _QUOTE_H
#define _QUOTE_H
#include <iostream>
#include <string>
class Quote
{
	public:
		Quote()=default;
		Quote(const std::string &book,double sales_price):price(sales_price),bookNo(book) {}
		std::string isbn() const {return bookNo;}
		virtual double net_price(std::size_t n) const {return n*price;}
		virtual std::string debug() const {return "bookNo="+bookNo+"\n"+"price="+std::to_string(price);}
		virtual ~Quote()=default;
	protected:
		double price=0.0;
	private:
		std::string bookNo;
};
class Disc_quote:public Quote
{
	public:
		Disc_quote()=default;
		Disc_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Quote(book,sales_price),quantity(qty),discount(disc) {}
		virtual double net_price(std::size_t n) const=0;
		virtual std::string debug() const override
		{
			return Quote::debug()+"\n"+"quantity="+std::to_string(quantity)+"\n"+"discount="+std::to_string(discount);
		}
	protected:
		std::size_t quantity=0;
		double discount=0.0;
};
double print_total(std::ostream &os,const Quote &item,std::size_t n);
class Bulk_quote:public Disc_quote
{
	public:
		Bulk_quote()=default;
		Bulk_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Disc_quote(book,sales_price,qty,disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n>=quantity)
				return n*(1-discount)*price;
			else
				return n*price;
		}
};
class Limit_quote:public Disc_quote
{
	public:
		Limit_quote()=default;
		Limit_quote(const std::string &book,double sales_price,std::size_t qty,double disc):Disc_quote(book,sales_price,qty,disc) {}
		virtual double net_price(std::size_t n) const override
		{
			if(n<=quantity)
				return n*(1-discount)*price;
			else
				return quantity*(1-discount)*price+(n-quantity)*price;
		}
};
#endif
```
==Quote.cpp==
```
#include "Quote.h"
double print_total(std::ostream &os,const Quote &item,std::size_t n)
{
	double ret=item.net_price(n);
	os<<"ISBN: "<<item.isbn()<<" # sold: "<<n<<" total due: "<<ret<<std::endl;
	return ret;
}
```
### 15.16
[见15.15](#2)
### 15.17
>>test.cpp:5:20: error: cannot declare variable ‘item’ to be of abstract type ‘Disc_quote’
