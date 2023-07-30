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
练习7.40中，编写的是Employee的框架，建议为其重载输入、输出运算符。
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
<a id="3">StrBlob.h</a>
```
#ifndef STRBLOB_H
#define STRBLOB_H
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
class StrBlobPtr;
class StrBlob
{
friend class StrBlobPtr;
friend bool operator==(const StrBlob &,const StrBlob &);
friend bool operator!=(const StrBlob &,const StrBlob &);
friend bool operator<(const StrBlob &,const StrBlob &);
friend bool operator>=(const StrBlob &,const StrBlob &);
friend bool operator>(const StrBlob &,const StrBlob &);
friend bool operator<=(const StrBlob &,const StrBlob &);
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	
	StrBlob(const StrBlob &);
	StrBlob & operator=(const StrBlob &);
	std::string & operator[](std::size_t i) {return data->at(i);}
	const std::string & operator[](std::size_t i) const {return data->at(i);}

	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
	void push_back(std::string &&t){data->push_back(std::move(t));}
	void pop_back();
	std::string &front();
	std::string &back();
	const std::string &front() const;
	const std::string &back() const;
	StrBlobPtr begin();
	StrBlobPtr begin() const;
	StrBlobPtr end();
	StrBlobPtr end() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i,const std::string &msg) const;
};
bool operator==(const StrBlob &,const StrBlob &);
bool operator!=(const StrBlob &,const StrBlob &);
bool operator<(const StrBlob &,const StrBlob &);
bool operator>=(const StrBlob &,const StrBlob &);
bool operator>(const StrBlob &,const StrBlob &);
bool operator<=(const StrBlob &,const StrBlob &);
class StrBlobPtr
{
friend bool operator==(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator!=(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator<(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator>=(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator>(const StrBlobPtr &,const StrBlobPtr &);
friend bool operator<=(const StrBlobPtr &,const StrBlobPtr &);
public:
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	StrBlobPtr(const StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	std::string & operator[](std::size_t i) {auto p=check(i,"index is out of range");return p->at(i);}
	const std::string & operator[](std::size_t i) const {auto p=check(i,"index is out of range");return p->at(i);}
	StrBlobPtr & operator++();
	StrBlobPtr operator++(int);
	StrBlobPtr & operator--();
	StrBlobPtr operator--(int);
	StrBlobPtr operator+(std::size_t) const;
	StrBlobPtr operator-(std::size_t) const;
	StrBlobPtr & operator+=(std::size_t);
	StrBlobPtr & operator-=(std::size_t);
	std::string & operator*() const;
	std::string * operator->() const;

	std::string &deref() const;
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string &) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr=0;
};
bool operator==(const StrBlobPtr &,const StrBlobPtr &);
bool operator!=(const StrBlobPtr &,const StrBlobPtr &);
bool operator<(const StrBlobPtr &,const StrBlobPtr &);
bool operator>=(const StrBlobPtr &,const StrBlobPtr &);
bool operator>(const StrBlobPtr &,const StrBlobPtr &);
bool operator<=(const StrBlobPtr &,const StrBlobPtr &);
#endif
```
==StrBlob.cpp==
```
#include "StrBlob.h"
using namespace std;
StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::begin() const
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this,data->size());
}
StrBlobPtr StrBlob::end() const
{
	return StrBlobPtr(*this,data->size());
}

StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
StrBlob::StrBlob(const StrBlob &org):data(make_shared<std::vector<std::string>>(*org.data)) {}
StrBlob & StrBlob::operator=(const StrBlob &rhs)
{
	data=make_shared<std::vector<std::string>>(*rhs.data);
	return *this;
}
inline void StrBlob::check(size_type i,const string &msg) const
{
	if(i>=data->size())
		throw out_of_range(msg);
}
string &StrBlob::front()
{
	check(0,"front on empty StrBlob");
	return data->front();
}
string &StrBlob::back()
{
	check(0,"back on empty StrBlob");
	return data->back();
}
const std::string &StrBlob::front() const
{
	check(0,"front on empty StrBlob");
	return data->front();
}
const std::string &StrBlob::back() const
{
	check(0,"back on empty StrBlob");
	return data->back();
}
void StrBlob::pop_back()
{
	check(0,"pop_back on empty StrBlob");
	data->pop_back();
}
bool operator==(const StrBlob &lhs,const StrBlob &rhs)
{
	return lhs.data==rhs.data;
}
bool operator!=(const StrBlob &lhs,const StrBlob &rhs)
{
	return !(lhs==rhs);
}
bool operator<(const StrBlob &lhs,const StrBlob &rhs)
{
	return *lhs.data<*rhs.data;
}
bool operator>=(const StrBlob &lhs,const StrBlob &rhs)
{
	return !(lhs<rhs);
}
bool operator>(const StrBlob &lhs,const StrBlob &rhs)
{
	return rhs<lhs;
}
bool operator<=(const StrBlob &lhs,const StrBlob &rhs)
{
	return !(rhs<lhs);
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i,const std::string &msg) const
{
	auto ret=wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if(i>=ret->size())
		throw std::out_of_range(msg);
	return ret;
}
std::string & StrBlobPtr::deref() const
{
	auto p=check(curr,"dereference past end");
	return (*p)[curr];
}
StrBlobPtr & StrBlobPtr::operator++()
{
	check(curr,"increment past end of StrBlobPtr");
	++curr;
	return *this;
}
StrBlobPtr StrBlobPtr::operator++(int)
{
	StrBlobPtr ret=*this;
	++*this;
	return ret;
}
StrBlobPtr & StrBlobPtr::operator--()
{
	--curr;
	check(curr,"decrement past the begin of StrBlobPtr");
	return *this;
}
StrBlobPtr StrBlobPtr::operator--(int)
{
	StrBlobPtr ret=*this;
	--*this;
	return ret;
}
StrBlobPtr StrBlobPtr::operator+(std::size_t i) const
{
	StrBlobPtr ret(*this);
	ret+=i;
	return ret;
}
StrBlobPtr StrBlobPtr::operator-(std::size_t i) const
{
	StrBlobPtr ret(*this);
	ret-=i;
	return ret;
}
StrBlobPtr & StrBlobPtr::operator+=(std::size_t i)
{
	while(i--)
		++*this;
	return *this;
}
StrBlobPtr & StrBlobPtr::operator-=(std::size_t i)
{
	check(curr-i,"decrement past begin of range");
	curr-=i;
	return *this;
}
std::string & StrBlobPtr::operator*() const
{
	auto p=check(curr,"dereference past end");
	return (*p)[curr];
}
std::string * StrBlobPtr::operator->() const
{
	return & this->operator*();
}
bool operator==(const StrBlobPtr &lhs,const StrBlobPtr &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r)
		return (!r||lhs.curr==rhs.curr);
	else
		return false;
}
bool operator!=(const StrBlobPtr &lhs,const StrBlobPtr &rhs)
{
	return !(lhs==rhs);
}
bool operator<(const StrBlobPtr &lhs,const StrBlobPtr &rhs)
{
	auto l=lhs.wptr.lock(),r=rhs.wptr.lock();
	if(l==r&&l)//两个指针未指向同一个vector的情况是否应该抛出异常
		return lhs.curr<rhs.curr;
	else
		return  false;
}
bool operator>=(const StrBlobPtr &lhs,const StrBlobPtr &rhs)
{
	return !(lhs<rhs);
}
bool operator>(const StrBlobPtr &lhs,const StrBlobPtr &rhs)
{
	return rhs<lhs;
}
bool operator<=(const StrBlobPtr &lhs,const StrBlobPtr &rhs)
{
	return !(rhs<lhs);
}
```
==StrVec.h==
```
#ifndef _STRVEC_H
#define _STRVEC_H
#include <string>
#include <cstddef>
#include <utility>
#include <memory>
#include <initializer_list>
class StrVec
{
	friend bool operator==(const StrVec &,const StrVec &);
	friend bool operator!=(const StrVec &,const StrVec &);
	friend bool operator<(const StrVec &,const StrVec &);
	friend bool operator>=(const StrVec &,const StrVec &);
	friend bool operator>(const StrVec &,const StrVec &);
	friend bool operator<=(const  StrVec &,const StrVec &);
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
		StrVec(const StrVec &);
		StrVec(std::initializer_list<std::string>);
		StrVec & operator=(const StrVec &);
		StrVec & operator=(std::initializer_list<std::string>);
		std::string & operator[](std::size_t i) {return elements[i];}
		const std::string & operator[](std::size_t i) const {return elements[i];}
		~StrVec() {free();}
		void push_back(const std::string &);
		size_t size() const {return first_free-elements;}
		size_t capacity() {return cap-elements;}
		std::string *begin() const {return elements;}
		std::string *end() const {return first_free;}

		void resize(const size_t n,const std::string &orgv=std::string());
		void reserve(const size_t n);
	private:
		std::string *elements;
		std::string *first_free;
		std::string *cap;
		static std::allocator<std::string> alloc;
		void chk_n_alloc() {if(size()==capacity()) reallocate();}
		std::pair<std::string *,std::string *> alloc_n_copy(const std::string *,const std::string *);
		void free();
		void reallocate();
};
bool operator==(const StrVec &,const StrVec &);
bool operator!=(const StrVec &,const StrVec &);
bool operator<(const StrVec &,const StrVec &);
bool operator>=(const StrVec &,const StrVec &);
bool operator>(const StrVec &,const StrVec &);
bool operator<=(const  StrVec &,const StrVec &);
#endif
```
==StrVec.cpp==
```
#include <algorithm>
#include "StrVec.h"
std::allocator<std::string> StrVec::alloc;
StrVec::StrVec(const StrVec &org)
{
	std::pair<std::string *,std::string *> data=alloc_n_copy(org.begin(),org.end());
	elements=data.first;
	first_free=cap=data.second;
}
StrVec::StrVec(std::initializer_list<std::string> ls)
{
	auto data=alloc_n_copy(ls.begin(),ls.end());
	elements=data.first;
	first_free=cap=data.second;
}
StrVec & StrVec::operator=(const StrVec &rhs)
{
	auto data=alloc_n_copy(rhs.begin(),rhs.end());
	free();
	elements=data.first;
	first_free=cap=data.second;
	return *this;
}
StrVec & StrVec::operator=(std::initializer_list<std::string> il)
{
	auto data=alloc_n_copy(il.begin(),il.end());
	free();
	elements=data.first;
	first_free=cap=data.second;
	return *this;
}
void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++,s);
}
std::pair<std::string *,std::string *> StrVec::alloc_n_copy(const std::string *b,const std::string *e)
{
	std::string *data=alloc.allocate(e-b);
	return {data,uninitialized_copy(b,e,data)};
}
void StrVec::free()
{
	if(elements)
	{
		for(auto p=first_free;p!=elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements,cap-elements);
	}
}
void StrVec::reallocate()
{
	size_t newcapacity=size()?2*size():1;
	std::string *newdata=alloc.allocate(newcapacity);
	std::string *dest=newdata;
	std::string *src=elements;
	for(size_t i=0;i!=size();++i)
		alloc.construct(dest++,std::move(*src++));
	free();
	elements=newdata;
	first_free=dest;
	cap=elements+newcapacity;
}
void StrVec::reserve(const size_t n)
{
	if(n>capacity())
	{
		std::string *newdata=alloc.allocate(n);
		std::string *dest=newdata;
		std::string *src=elements;
		for(size_t i=0;i!=size();++i)
			alloc.construct(dest++,std::move(*src++));
		free();
		elements=newdata;
		first_free=dest;
		cap=elements+n;
	}
}
void StrVec::resize(const size_t n,const std::string &orgv)
{
	if(n<=size())
	{
		std::string *b=elements+n;
		std::string *e=first_free;
		while(b!=e)
			alloc.destroy(b++);
		first_free=elements+n;
	}
	else if(n<=capacity())
	{
		std::string *b=first_free;
		std::string *e=elements+n;
		while(b!=e)
			alloc.construct(b++,orgv);
		first_free=e;
	}
	else
	{
		reserve(n);
		std::string *b=first_free;
		std::string *e=elements+n;
		while(b!=e)
			alloc.construct(b++,orgv);
		first_free=e;
	}
}
bool operator==(const StrVec &lhs,const StrVec &rhs)
{
	return (lhs.size()==rhs.size())&&std::equal(lhs.begin(),lhs.end(),rhs.begin());
}
bool operator!=(const StrVec &lhs,const StrVec &rhs)
{
	return !(lhs==rhs);
}
bool operator<(const StrVec &lhs,const StrVec &rhs)
{
	return lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}
bool operator>=(const StrVec &lhs,const StrVec &rhs)
{
	return !(lhs<rhs);
}
bool operator>(const StrVec &lhs,const StrVec &rhs)
{
	return rhs<lhs;
}
bool operator<=(const  StrVec &lhs,const StrVec &rhs)
{
	return !(rhs<lhs);
}
```
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
	friend bool operator==(const String &,const String &);
	friend bool operator!=(const String &,const String &);
	friend bool operator<(const String &,const String &);
	friend bool operator>=(const String &,const String &);
	friend bool operator>(const String &,const String &);
	friend bool operator<=(const String &,const String &);
	public:
		String():head(nullptr),tail(nullptr),cap(nullptr) {}
		String(const char *);
		String(const String &);
		String(String &&str) noexcept :head(str.head),tail(str.tail),cap(str.cap) {str.head=str.tail=str.cap=nullptr;std::cout<<"This is move constructor."<<std::endl;}
		String & operator=(const String &);
		String & operator=(String &&);
		String operator+(const String &);
		char & operator[](std::size_t i) {return head[i];}
		const char & operator[](std::size_t i) const {return head[i];}
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
bool operator==(const String &,const String &);
bool operator!=(const String &,const String &);
bool operator<(const String &,const String &);
bool operator>=(const String &,const String &);
bool operator>(const String &,const String &);
bool operator<=(const String &,const String &);
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
	std::pair<char *,char *> newdata=alloc_n_copy(s.begin(),s.end());
	head=newdata.first;
	tail=cap=newdata.second;
}
String & String::operator=(const String &rhs)
{
	std::pair<char *,char *> newdata=alloc_n_copy(rhs.begin(),rhs.end());
	free();
	head=newdata.first;
	tail=cap=newdata.second;
	return *this;
}
String & String::operator=(String &&rhs)
{
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
bool operator==(const String &lhs,const String &rhs)
{
	return (lhs.size()==rhs.size())&&std::equal(lhs.begin(),lhs.end(),rhs.begin());
}
bool operator!=(const String &lhs,const String &rhs)
{
	return !(lhs==rhs);
}
bool operator<(const String &lhs,const String &rhs)
{
	size_t i=0;
	size_t l_size=lhs.size(),r_size=rhs.size();
	while(i<l_size&&i<r_size)
	{
		if(*(lhs.begin()+i)==*(rhs.begin()+i))
			++i;
		else
			return *(lhs.begin()+i)<*(rhs.begin()+i);
	}
	return l_size<r_size;
}
bool operator>=(const String &lhs,const String &rhs)
{
	return !(lhs<rhs);
}
bool operator>(const String &lhs,const String &rhs)
{
	return rhs<lhs;
}
bool operator<=(const String &lhs,const String &rhs)
{
	return !(rhs<lhs);
}
```
### 14.17
<a id="4">Employee.h</a>
```
#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H
#include <iostream>
class Employee
{
	friend std::ostream & operator<<(std::ostream &,const Employee &);
	friend std::istream & operator>>(std::istream &,Employee &);
	friend bool operator==(const Employee &,const Employee &);
	friend bool operator!=(const Employee &,const Employee &);
	public:
		Employee()=default;
		Employee(std::string s):name(s){}
		Employee(std::string s,unsigned int i,double j,unsigned int k):name(s),Age(i),salary(j),Phone_Number(k){}
		Employee & operator=(const Employee &);
		Employee & operator=(Employee &&);
		Employee & operator=(const std::string &);
		operator bool()  const {return !(name.empty());}
	private:
		std::string name;
		unsigned int Age=0;
		double salary=0;
		unsigned int Phone_Number=0;
};
std::ostream & operator<<(std::ostream &,const Employee &);
std::istream & operator>>(std::istream &,Employee &);
bool operator==(const Employee &,const Employee &);
bool operator!=(const Employee &,const Employee &);
#endif
```
==Employee.cpp==
```
#include "Employee.h"
Employee & Employee::operator=(const Employee &rhs)
{
	name=rhs.name;
	Age=rhs.Age;
	salary=rhs.salary;
	Phone_Number=rhs.Phone_Number;
	return *this;
}
Employee & Employee::operator=(Employee &&rhs)
{
	if(this!=&rhs)
	{
		name=std::move(rhs.name);
		Age=rhs.Age;
		salary=rhs.salary;
		Phone_Number=rhs.Phone_Number;
	}
	return *this;
}
Employee & Employee::operator=(const std::string &str)
{
	name=str;
	return *this;
}
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
bool operator==(const Employee &lhs,const Employee &rhs)
{
	return lhs.name==rhs.name&&lhs.Age==rhs.Age&&lhs.salary==rhs.salary&&lhs.Phone_Number==rhs.Phone_Number;
}
bool operator!=(const Employee &lhs,const Employee &rhs)
{
	return !(lhs==rhs);
}
```
### 14.18
[见14.16](#3)
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
<a id="5">Sales_data.h</a>
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
### 14.23
[见14.16](#3)
### 14.24
[见14.17](#4)
### 14.25
[见14.17](#4)
需要定义一个运算对象为string的赋值运算符，可以直接为雇员的名字赋值.
### 14.26
[见14.16](#3)
### 14.27
[见14.16](#3)
### 14.28
[见14.16](#3)
### 14.29
因为递增、递减运算符要改变所操作对象的状态，所以不能使用const修饰符。
### 14.30
[见14.16](#3)
### 14.31
因为StrBlobPtr的数据成员是由一个weak_ptr和一个内置类型组成，它们都能被合成的拷贝控制成员正确的处理。
### 14.32
==PtStrBlobPtr.h==
```
#ifndef _PTSTRBLOBPTR_H
#define _PTSTRBLOBPTR_H
#include "StrBlob.h"
class PtStrBlobPtr
{
	public:
		PtStrBlobPtr()=default;
		PtStrBlobPtr(StrBlobPtr *p):ptbp(p) {}
		StrBlobPtr & operator*() const {return *ptbp;}
		StrBlobPtr * operator->() const {return & this->operator*();}
	private:
		StrBlobPtr * ptbp=nullptr;
};
#endif
```
==PtStrBlobPtr.cpp==
```
#include "PtStrBlobPtr.h"
```
### 14.33
因为重载的函数调用运算符可接受的参数是不一定的，所以它应该接受几个运算对象不确定。
### 14.34
```
#include <iostream>
struct func
{
	int operator()(int a,int b,int c) { return a>0?b:c;}
};
int main(void)
{
	func f;
	std::cout<<f(-1,2,3)<<std::endl;
	return 0;
}
```
### 14.35
```
#include <iostream>
#include <string>
struct func
{
	std::string operator()()
	{
		std::string tmp;
		getline(std::cin,tmp);
		return tmp;
	}
};
int main(void)
{
	func f;
	std::cout<<f()<<std::endl;
	return 0;
}
```
### 14.36
```
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
struct func
{
	std::string operator()()
	{
		std::string tmp;
		getline(std::cin,tmp);
		return tmp;
	}
};
int main(void)
{
	vector<string> svec;
	func f;
	while(cin)
		svec.push_back(f());
	for(const auto a:svec)
		cout<<a<<endl;
	return 0;
}
```
### 14.37
```
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
class func
{
	public:
		func(int tg=0):targ(tg) {}
		bool operator()(int rec) {return rec==targ;}
	private:
		int targ=0;
};
int main(void)
{
	func f(1);
	vector<int> a{0,1,2,1,3,4,5},b;
	replace_copy_if(a.begin(),a.end(),back_inserter(b),f,99);
	for(auto r:b)
		cout<<r<<endl;
	return 0;
}
```
### 14.38
```
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class func
{
	public:
		func(size_t n):sz(n) {}
		bool operator()(const string &str) {return str.size()==sz;}
	private:
		size_t sz=0;
};
int main(int argc,char *argv[])
{
	string tmp;
	size_t wl1=0,wl2=0,wl10=0;
	func f1(1),f2(2),f10(10);
	ifstream  in(argv[1]);
	while(in>>tmp)
	{
		if(f1(tmp))
			++wl1;
		if(f2(tmp))
			++wl2;
		if(f10(tmp))
			++wl10;
	}
	in.close();
	cout<<"长度为1的单词有"<<wl1<<" 长度为2的单词有"<<wl2<<" 长度为10的单词有"<<wl10<<endl;
	return 0;
}
```
### 14.39
```
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class func
{
	public:
		func(size_t n):sz(n) {}
		bool operator()(const string &str) {return str.size()>sz;}
	private:
		size_t sz=0;
};
int main(int argc,char *argv[])
{
	string tmp;
	size_t wl1=0,wl2=0,wl10=0;
	func f1(0),f2(9),f10(10);
	ifstream  in(argv[1]);
	while(in>>tmp)
	{
		if(f1(tmp))
			++wl1;
		if(f2(tmp))
			++wl2;
		if(f10(tmp))
			++wl10;
	}
	in.close();
	cout<<"长度为1-9的单词有"<<wl1-wl2<<" 长度大于10的单词有"<<wl10<<endl;
	return 0;
}
```
### 14-40
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
struct func1
{
	bool operator()(const string &str1,const string &str2) {return str1.size()<str2.size();}
};
class func2
{
	public:
		func2(size_t n):sz(n) {}
		bool operator()(const string &str) {return str.size()>=sz;}
	private:
		size_t sz;
};
struct func3
{
	void operator()(const string &str) {cout<<str<<" ";}
};
void elimDups(vector<string> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),func1());
	auto wc=find_if(words.begin(),words.end(),func2(sz));
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" of length "<<sz<<" or longer "<<endl;
	for_each(wc,words.end(),func3());
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,3);
	return 0;
}
```
### 14.41
lambda就是匿名的函数对象，当这个函数对象只在少数地方使用，并且函数体足够简单时，适合使用lambda表达式。而这个函数对象需要多次复用，并且函数体较复杂时，使用类。
### 14.42
- 
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
void elimDups(vector<int> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<int> &words,vector<int>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),less<int>());
	auto wc=find_if(words.begin(),words.end(),bind(greater<int>(),std::placeholders::_1,sz));//在这里
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" greater than "<<sz<<endl;
	cout<<endl;
}
int main(void)
{
	int tmp;
	vector<int> ivec;
	cout<<"Enter some integers: ";
	while(cin>>tmp)
		ivec.push_back(tmp);
	biggies(ivec,1024);
	return 0;
}
```
- 
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	auto wc=find_if(svec.begin(),svec.end(),bind(not_equal_to<string>(),std::placeholders::_1,"pooh"));//在这里
	if(wc==svec.end())
		cout<<"All are pooh."<<endl;
	else
		cout<<"Find the string not equal to pooh."<<endl;
	return 0;
}
```
- 
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
int main(void)
{
	int tmp;
	vector<int> ivec,ivec_backup;
	cout<<"Enter some integers: ";
	while(cin>>tmp)
		ivec.push_back(tmp);
	transform(ivec.begin(),ivec.end(),back_inserter(ivec_backup),bind(multiplies<int>(),std::placeholders::_1,2));//在这里
	cout<<"multiply by two:";
	for(auto i:ivec_backup)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
```
### 14.43
```
#include <iostream>
#include <vector>
#include <functional>
using namespace std;
int main(void)
{
	bool flag=true;
	int targ,tmp;
	vector<int> ivec;
	cout<<"输入要判断的那个int值:";
	cin>>targ;
	cout<<"输入一系列int值创建一个int容器:";
	while(cin>>tmp)
		ivec.push_back(tmp);
	for(const int &i:ivec)
	{
		if(modulus<int>()(targ,i)!=0)
		{
			flag=false;
			break;
		}
	}
	if(flag)
		cout<<"可以被整除"<<endl;
	else
		cout<<"不能被整除"<<endl;
	return 0;
}
```
### 14.44
```
#include <iostream>
#include <map>
#include <functional>
#include <string>
using namespace std;
int add(int i,int j) {return i+j;}
int main(void)
{
	struct divide
	{
		int operator()(int denominator,int divisor) {return denominator/divisor;}
	};
	auto mod=[](int x,int y)->int {return x%y;};
	map<string,function<int(int,int)>> binops=
	{
		{"+",add},
		{"-",minus<int>()},
		{"*",[](int x,int y) {return x*y;}},
		{"/",divide()},
		{"%",mod}
	};
	int a,b;
	string op;
	cout<<"输入 数字 算术符号 数字:";
	cin>>a>>op>>b;
	cout<<"结果是"<<binops[op](a,b)<<endl;
	return 0;
}
```
### 14.45
[见14.22](#5)
转换为string时应该返回bookNo。转换为double时到底应该返回revenue还是返回avg_price不确定，它们之间不存在明确的一对一对应关系。
### 14.46
可以为Sales_data定义string类型转换运算符，但建议声明成explicit,可以防止在某些情况下被默认转换成string,导致意料之外的运算结果。不建议定义double类型转换运算符，因为它不存在明确的一对一对应关系。
### 14.47
- 转换为const int
- 转换为int，此const表示const函数,即不会修改待转换对象内容。
### 14.48
它应该含有向bool的类型转换运算符，并且应该是explicit的，可以避免被默认转换成bool，导致意料之外的运算结果。此类型转换可以用在条件判断处，而explicit的类型转换运算符用在条件判断时可以被隐式的执行。
### 14.49
[见14.17](#4)
### 14.50
- 因为没有直接转换为int型的用户定义的类型转换，所以得先转换为算术类型，再执行算术类型转换。而第一步中两个用户定义的类型转换一样好，所以产生二义性。
- 直接调用operator float()类型转换。
### 14.51
会直接调用`void calc(int)`，因为标准类型转换优先于用户定义的类型转换。
### 14.52
- 二义性调用
- 1，2都可以，1成员函数是精确匹配，2中si需要先利用用户定义的类型转换，转换为int，再进行标准类型转换，转换为double。所以调用1.
### 14.53
不合法，会产生二义性。SmallInt可以转换为int调用内置类型的+号，3.14可以转换为SmallInt而调用其重载的+号。可以这样该`double d=s1+SmallInt(3.14)`。
