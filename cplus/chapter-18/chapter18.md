[toc]
### 18.1
1. 此时r是一个range_error类型的局部对象
2. 此时p是exception类型的指针,指向局部对象r
如果`throw p`就会抛出一个指向局部对象的指针，那么有可能在执行catch语句之前，该局部对象已经被销毁。
### 18.2
v和in可以调用其析构函数释放资源，而p无法正确释放资源，导致内存泄漏。
### 18.3
1. 使用智能指针管理p
`unique_ptr<int []> p(new int[v.size()])`
2. 使用类来控制资源的分配
```
class ptr
{
	public:
		explicit ptr(size_t len):p(new int[len]) {}
		ptr(const ptr&)=delete;
		ptr & operator=(const ptr&)=delete;
		~ptr()
		{
			delete [] p;
		}
	private:
		int *p;
};
```
### 18.4
catch语句是按照其出现的顺序逐一进行匹配的，所以根据继承体系`catch(exception)`后面的catch子句永远无法被匹配到。
```
try{
//
}catch(overflow_error eobj){
//
}catch(const runtime_error &re){
//
}catch(exception){/**/}
```
### 18.5
```
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
int main(){
	try{
		//使用c++标准库
}catch(const exception &e){
	std::cout<<e.what()<<std::endl;
	abort();
}
}
```
### 18.6
1. `throw exceptionType * eobj`，注意不能抛出一个指向局部对象的指针
2. 抛出的所有异常都能被捕获
3. `int a=1;throw a;`抛出的所有int类型值都能被捕获，但是其余的整型类型无法进行算数类型转换为int。
### 18.7
```
#ifndef BLOB_H
#define BLOB_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
template <typename> class BlobPtr;
template <typename> class Blob;
//Blob
template <typename T> bool operator==(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator!=(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator<(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator<=(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator>(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator>=(const Blob<T> &,const Blob<T> &);
template <typename T> class Blob
{
	friend class BlobPtr<T>;
	friend bool operator==<T>(const Blob<T> &,const Blob<T> &);
	friend bool operator!=<T>(const Blob<T> &,const Blob<T> &);
	friend bool operator< <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator<= <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator> <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator>= <T>(const Blob<T> &,const Blob<T> &);
	public:
		typedef T value_type;
		typedef typename std::vector<T>::size_type size_type;
		Blob() try:data(std::make_shared<std::vector<T>>()){} catch(std::bad_alloc &e){std::cout<<e.what()<<std::endl;}
		Blob(std::initializer_list<T> il) try:data(std::make_shared<std::vector<T>>(il)){} catch(std::bad_alloc &e){std::cout<<e.what()<<std::endl;}
		Blob(const Blob &org) try:data(std::make_shared<std::vector<T>>(*org.data)){} catch(std::bad_alloc &e){std::cout<<e.what()<<std::endl;}
		template <typename it> Blob(it b,it e) try:data(std::make_shared<std::vector<T>>(b,e)) {} catch(std::bad_alloc &ba){std::cout<<ba.what()<<std::endl;}
		Blob &operator=(const Blob &);
		T & operator[](size_type i);
		const T & operator[](size_type i) const;
		size_type size() const {return data->size();}
		bool empty() const {return data->empty;}
		void push_back(const T &t){data->push_back(t);}
		void push_back(T &&t){data->push_back(std::move(t));}
		void pop_back();
		T & front();
		T & back();
		const T & front() const;
		const T & back() const;
		BlobPtr<T> begin();
		BlobPtr<T> end();
	private:
		std::shared_ptr<std::vector<T>> data;
		void check(size_type i,const std::string &msg) const;
};
//BlobPtr
template <typename T> bool operator==(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator!=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator<(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator<=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator>(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator>=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> class BlobPtr
{
	friend bool operator==<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator!=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator< <T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator<=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator><T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator>=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	public:
		typedef typename std::vector<T>::size_type size_type;
		BlobPtr():curr(0){}
		BlobPtr(const Blob<T> &blob,size_type sz=0):wptr(blob.data),curr(sz){}
		T & operator[](size_type i);
		const T & operator[](size_type i) const;
		BlobPtr & operator++();
		BlobPtr & operator++(int);
		BlobPtr & operator--();
		BlobPtr & operator--(int);
		BlobPtr operator+(size_type) const;
		BlobPtr operator-(size_type) const;
		BlobPtr operator+=(size_type) const;
		BlobPtr operator-=(size_type) const;
		T & operator*() const;
		T * operator->() const;
	private:
		std::shared_ptr<std::vector<T>> check(size_type i,const std::string &msg) const;
		std::weak_ptr<std::vector<T>> wptr;
		size_type curr=0;
};
//Blob
template <typename T> Blob<T> & Blob<T>::operator=(const Blob &rhs)
{
	data=std::make_shared<std::vector<T>>(*rhs.data);
	return *this;
}
template <typename T> T & Blob<T>::operator[](size_type i)
{
	check(i,"subscript out of range");
	return (*data)[i];
}
template <typename T> const T & Blob<T>::operator[](size_type i) const
{
	check(i,"subscript out of range");
	return (*data)[i];
}
template <typename T> void Blob<T>::pop_back()
{
	check(0,"pop_back on empty Blob");
	data->pop_back();
}
template <typename T> T & Blob<T>::front()
{
	check(0,"front on empty Blob");
	return data->front();
}
template <typename T> const T & Blob<T>::front() const
{
	check(0,"front on empty Blob");
	return data->front();
}
template <typename T> T & Blob<T>::back()
{
	check(0,"back on empty Blob");
	return data->back();
}
template <typename T> const T & Blob<T>::back() const
{
	check(0,"back on empty Blob");
	return data->back();
}
template <typename T> BlobPtr<T> Blob<T>::begin()
{
	return BlobPtr<T>(*this);
}
template <typename T> BlobPtr<T> Blob<T>::end()
{
	return BlobPtr<T>(*this,data->size());
}
template <typename T> inline void Blob<T>::check(size_type i,const std::string &msg) const
{
	if(i>=data->size())
		throw std::out_of_range(msg);
}
template <typename T> bool operator==(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data==*rhs.data;
}
template <typename T> bool operator!=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data<*rhs.data;
}
template <typename T> bool operator<=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs>rhs);
}
template <typename T> bool operator>(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data>*rhs.data;
}
template <typename T> bool operator>=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs<rhs);
}
//BlobPtr
template <typename T> std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_type i,const std::string &msg) const
{
	auto ret=wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound BlobPtr");
	if(i>=ret->size())
		throw std::out_of_range(msg);
	return ret;
}
template <typename T> T & BlobPtr<T>::operator[](size_type i)
{
	auto ret=check(i,"index out of range");
	return (*ret)[i];
}
template <typename T> const T & BlobPtr<T>::operator[](size_type i) const
{
	auto ret=check(i,"index out of range");
	return (*ret)[i];
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator++()
{
	check(curr,"increment past end of BlobPtr");
	++curr;
	return *this;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator++(int)
{
	BlobPtr ret=*this;
	++*this;
	return ret;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator--()
{
	--curr;
	check(curr,"decrement past the begin of BlobPtr");
	return *this;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator--(int)
{
	BlobPtr ret=*this;
	--*this;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator+(size_type i) const
{
	BlobPtr ret(*this);
	ret+=i;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator-(size_type i) const
{
	BlobPtr ret(*this);
	ret-=i;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator+=(size_type i) const
{
	check(curr+i,"increment past end of range");
	while(--i)
		++*this;
	return *this;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator-=(size_type i) const
{
	check(curr-i,"decrement past begin of range");
	while(--i)
		--*this;
	return *this;
}
template <typename T> T & BlobPtr<T>::operator*() const
{
	auto p=check(curr,"dereference past end");
	return (*p)[curr];
}
template <typename T> T * BlobPtr<T>::operator->() const
{
	return & this->operator*();
}
template <typename T> bool operator==(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r)
		return (!r||lhs.curr==rhs.curr);
	else
		return false;
}
template <typename T> bool operator!=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r&&l)
		return lhs.curr<rhs.curr;
	else
		return false;
}
template <typename T> bool operator<=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs>rhs);
}
template <typename T> bool operator>(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return rhs<lhs;
}
template <typename T> bool operator>=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs<rhs);
}
#endif
```
### 18.8
```
#ifndef BLOB_H
#define BLOB_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
template <typename> class BlobPtr;
template <typename> class Blob;
//Blob
template <typename T> bool operator==(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator!=(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator<(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator<=(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator>(const Blob<T> &,const Blob<T> &);
template <typename T> bool operator>=(const Blob<T> &,const Blob<T> &);
template <typename T> class Blob
{
	friend class BlobPtr<T>;
	friend bool operator==<T>(const Blob<T> &,const Blob<T> &);
	friend bool operator!=<T>(const Blob<T> &,const Blob<T> &);
	friend bool operator< <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator<= <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator> <T>(const Blob<T> &,const Blob<T> &);
	friend bool operator>= <T>(const Blob<T> &,const Blob<T> &);
	public:
		typedef T value_type;
		typedef typename std::vector<T>::size_type size_type;
		Blob() noexcept(false) try:data(std::make_shared<std::vector<T>>()){} catch(std::bad_alloc &e){std::cout<<e.what()<<std::endl;}
		Blob(std::initializer_list<T> il) noexcept(false) try:data(std::make_shared<std::vector<T>>(il)){} catch(std::bad_alloc &e){std::cout<<e.what()<<std::endl;}
		Blob(const Blob &org) noexcept(false) try:data(std::make_shared<std::vector<T>>(*org.data)){} catch(std::bad_alloc &e){std::cout<<e.what()<<std::endl;}
		template <typename it> Blob(it b,it e) noexcept(false) try:data(std::make_shared<std::vector<T>>(b,e)) {} catch(std::bad_alloc &ba){std::cout<<ba.what()<<std::endl;}
		Blob &operator=(const Blob &);
		T & operator[](size_type i);
		const T & operator[](size_type i) const;
		size_type size() const {return data->size();}
		bool empty() const {return data->empty;}
		void push_back(const T &t){data->push_back(t);}
		void push_back(T &&t){data->push_back(std::move(t));}
		void pop_back();
		T & front();
		T & back();
		const T & front() const;
		const T & back() const;
		BlobPtr<T> begin();
		BlobPtr<T> end();
		~Blob() noexcept {};
	private:
		std::shared_ptr<std::vector<T>> data;
		void check(size_type i,const std::string &msg) const;
};
//BlobPtr
template <typename T> bool operator==(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator!=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator<(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator<=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator>(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> bool operator>=(const BlobPtr<T> &,const BlobPtr<T> &);
template <typename T> class BlobPtr
{
	friend bool operator==<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator!=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator< <T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator<=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator><T>(const BlobPtr<T> &,const BlobPtr<T> &);
	friend bool operator>=<T>(const BlobPtr<T> &,const BlobPtr<T> &);
	public:
		typedef typename std::vector<T>::size_type size_type;
		BlobPtr():curr(0){}
		BlobPtr(const Blob<T> &blob,size_type sz=0):wptr(blob.data),curr(sz){}
		T & operator[](size_type i);
		const T & operator[](size_type i) const;
		BlobPtr & operator++();
		BlobPtr & operator++(int);
		BlobPtr & operator--();
		BlobPtr & operator--(int);
		BlobPtr operator+(size_type) const;
		BlobPtr operator-(size_type) const;
		BlobPtr operator+=(size_type) const;
		BlobPtr operator-=(size_type) const;
		T & operator*() const;
		T * operator->() const;
	private:
		std::shared_ptr<std::vector<T>> check(size_type i,const std::string &msg) const;
		std::weak_ptr<std::vector<T>> wptr;
		size_type curr=0;
};
//Blob
template <typename T> Blob<T> & Blob<T>::operator=(const Blob &rhs)
{
	data=std::make_shared<std::vector<T>>(*rhs.data);
	return *this;
}
template <typename T> T & Blob<T>::operator[](size_type i)
{
	check(i,"subscript out of range");
	return (*data)[i];
}
template <typename T> const T & Blob<T>::operator[](size_type i) const
{
	check(i,"subscript out of range");
	return (*data)[i];
}
template <typename T> void Blob<T>::pop_back()
{
	check(0,"pop_back on empty Blob");
	data->pop_back();
}
template <typename T> T & Blob<T>::front()
{
	check(0,"front on empty Blob");
	return data->front();
}
template <typename T> const T & Blob<T>::front() const
{
	check(0,"front on empty Blob");
	return data->front();
}
template <typename T> T & Blob<T>::back()
{
	check(0,"back on empty Blob");
	return data->back();
}
template <typename T> const T & Blob<T>::back() const
{
	check(0,"back on empty Blob");
	return data->back();
}
template <typename T> BlobPtr<T> Blob<T>::begin()
{
	return BlobPtr<T>(*this);
}
template <typename T> BlobPtr<T> Blob<T>::end()
{
	return BlobPtr<T>(*this,data->size());
}
template <typename T> inline void Blob<T>::check(size_type i,const std::string &msg) const
{
	if(i>=data->size())
		throw std::out_of_range(msg);
}
template <typename T> bool operator==(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data==*rhs.data;
}
template <typename T> bool operator!=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data<*rhs.data;
}
template <typename T> bool operator<=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs>rhs);
}
template <typename T> bool operator>(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return *lhs.data>*rhs.data;
}
template <typename T> bool operator>=(const Blob<T> &lhs,const Blob<T> &rhs)
{
	return !(lhs<rhs);
}
//BlobPtr
template <typename T> std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_type i,const std::string &msg) const
{
	auto ret=wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound BlobPtr");
	if(i>=ret->size())
		throw std::out_of_range(msg);
	return ret;
}
template <typename T> T & BlobPtr<T>::operator[](size_type i)
{
	auto ret=check(i,"index out of range");
	return (*ret)[i];
}
template <typename T> const T & BlobPtr<T>::operator[](size_type i) const
{
	auto ret=check(i,"index out of range");
	return (*ret)[i];
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator++()
{
	check(curr,"increment past end of BlobPtr");
	++curr;
	return *this;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator++(int)
{
	BlobPtr ret=*this;
	++*this;
	return ret;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator--()
{
	--curr;
	check(curr,"decrement past the begin of BlobPtr");
	return *this;
}
template <typename T> BlobPtr<T> & BlobPtr<T>::operator--(int)
{
	BlobPtr ret=*this;
	--*this;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator+(size_type i) const
{
	BlobPtr ret(*this);
	ret+=i;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator-(size_type i) const
{
	BlobPtr ret(*this);
	ret-=i;
	return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator+=(size_type i) const
{
	check(curr+i,"increment past end of range");
	while(--i)
		++*this;
	return *this;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator-=(size_type i) const
{
	check(curr-i,"decrement past begin of range");
	while(--i)
		--*this;
	return *this;
}
template <typename T> T & BlobPtr<T>::operator*() const
{
	auto p=check(curr,"dereference past end");
	return (*p)[curr];
}
template <typename T> T * BlobPtr<T>::operator->() const
{
	return & this->operator*();
}
template <typename T> bool operator==(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r)
		return (!r||lhs.curr==rhs.curr);
	else
		return false;
}
template <typename T> bool operator!=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs==rhs);
}
template <typename T> bool operator<(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	auto l=lhs.wptr.lock();
	auto r=rhs.wptr.lock();
	if(l==r&&l)
		return lhs.curr<rhs.curr;
	else
		return false;
}
template <typename T> bool operator<=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs>rhs);
}
template <typename T> bool operator>(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return rhs<lhs;
}
template <typename T> bool operator>=(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
	return !(lhs<rhs);
}
#endif
```
### 18.9
<a id="1">Sales_data.h</a>
```
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
	private:
		std::string bookNo;
		unsigned units_sold=0;
		double revenue=0.0;
		double avg_price() const;
};
std::istream & operator>>(std::istream &,Sales_data &);
std::ostream & operator<<(std::ostream &,const Sales_data &);
Sales_data operator+(const Sales_data &,const Sales_data &);
bool compareIsbn(const Sales_data &lhs,const Sales_data &rhs);
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
	if(lhs.isbn()!=rhs.isbn())
		throw isbn_mismatch("wrong isbns!",lhs.isbn(),rhs.isbn());
	tmp.bookNo=lhs.bookNo;
	tmp.units_sold=lhs.units_sold+rhs.units_sold;
	tmp.revenue=lhs.revenue+rhs.revenue;
	return tmp;
}
bool compareIsbn(const Sales_data &lhs,const Sales_data &rhs)
{
	return lhs.isbn()<rhs.isbn();
}
```
==test1.cpp==
```
#include <iostream>
#include "Sales_data.h"
int main(void)
{
	Sales_data a("111",2,30),b("112",3,50);
	a+b;
	return  0;
}
```
不处理异常的输出
terminate called after throwing an instance of 'isbn_mismatch'
  what():  wrong isbns!
Aborted
==test2.cpp==
```
#include <iostream>
#include "Sales_data.h"
int main(void)
{
	Sales_data a("111",2,30),b("112",3,50);
	try
	{
		a+b;
	}
	catch(const isbn_mismatch &e)
	{
		std::cerr<<e.what()<<": left isbn ("<<e.left<<") right isbn ("<<e.right<<")"<<std::endl;
	}
	return  0;
}
```
处理异常的输出
wrong isbns!: left isbn (111) right isbn (112)
### 18.10
[见18.9](#1)
### 18.11
如果what函数抛出异常的话，没有对应的catch子句捕获处理，就会调用terminate使程序结束，破坏正常逻辑。
