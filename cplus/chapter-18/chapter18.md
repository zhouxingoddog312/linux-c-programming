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
### 18.12
==Query.h==
```
#ifndef _QUERY_H
#define _QUERY_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
namespace chapter15
{
	class QueryResult;
	class TextQuery
	{
		public:
			using line_no=std::vector<std::string>::size_type;
			TextQuery(std::ifstream &);
			QueryResult query(const std::string &) const;
		private:
			std::shared_ptr<std::vector<std::string>> file;
			std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
	};
	class QueryResult
	{
		friend std::ostream &print(std::ostream &,const QueryResult &);
		public:
			QueryResult(std::string s,std::shared_ptr<std::set<std::vector<std::string>::size_type>> l,std::shared_ptr<std::vector<std::string>> f):sought(s),lines(l),file(f){}
			std::set<std::vector<std::string>::size_type>::iterator begin() const {return lines->begin();}
			std::set<std::vector<std::string>::size_type>::iterator end() const {return lines->end();}
			std::shared_ptr<std::vector<std::string>> get_file(){return file;}
		private:
			std::string sought;
			std::shared_ptr<std::set<std::vector<std::string>::size_type>> lines;
			std::shared_ptr<std::vector<std::string>> file;
	};
	std::ostream &print(std::ostream &,const QueryResult &);
	inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
	{
		return (count>1)?word+ending:word;
	}
	class Query_base
	{
		friend class Query;
		protected:
			using line_no=TextQuery::line_no;
			virtual ~Query_base()=default;
		private:
			virtual QueryResult eval(const TextQuery &) const=0;
			virtual std::string rep() const=0;
	};
	class Query
	{
		friend Query operator~(const Query &);
		friend Query operator&(const Query &,const Query &);
		friend Query operator|(const Query &,const Query &);
		public:
			Query(const std::string &);
			QueryResult eval(const TextQuery &t) const {return q->eval(t);}
			std::string rep() const {return q->rep();}
		private:
			Query(std::shared_ptr<Query_base> query):q(query) {}
			std::shared_ptr<Query_base> q;
	};
	class WordQuery:public Query_base
	{
		friend class Query;
		private:
			WordQuery(const std::string &s):query_word(s) {}
			virtual QueryResult eval(const TextQuery &t) const {return t.query(query_word);}
			virtual std::string rep() const {return query_word;}
			std::string query_word;
	};
	
	inline Query::Query(const std::string &s):q(new WordQuery(s)) {}
	
	class NotQuery:public Query_base
	{
		friend Query operator~(const Query &);
		private:
			NotQuery(const Query &q):query(q) {}
			virtual QueryResult eval(const TextQuery &) const;
			virtual std::string rep() const {return "~("+query.rep()+")";}
			Query query;
	};
	inline Query operator~(const Query &q) {return std::shared_ptr<Query_base>(new NotQuery(q));}
	class BinaryQuery:public Query_base
	{
		protected:
			BinaryQuery(const Query &left,const Query &right,const std::string &s):lhs(left),rhs(right),opSym(s) {}
			virtual std::string rep() const {return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";}
			Query lhs,rhs;
			std::string opSym;
	};
	class AndQuery:public BinaryQuery
	{
		friend Query operator&(const Query&,const Query&);
		private:
			AndQuery(const Query &left,const Query &right):BinaryQuery(left,right,"&") {}
			virtual QueryResult eval(const TextQuery &) const;
	};
	inline Query operator&(const Query &left,const Query &right) {return std::shared_ptr<Query_base>(new AndQuery(left,right));}
	class OrQuery:public BinaryQuery
	{
		friend Query operator|(const Query &,const Query &);
		private:
			OrQuery(const Query &left,const Query &right):BinaryQuery(left,right,"|") {}
			virtual QueryResult eval(const TextQuery &) const;
	};
	inline Query operator|(const Query &left,const Query &right) {return std::shared_ptr<Query_base>(new OrQuery(left,right));}
	inline std::ostream & operator<<(std::ostream &os,const Query &q) {return os<<q.rep();}
}
#endif
```
==Query.cpp==
```
#include <sstream>
#include <algorithm>
#include <cctype>
#include "Query.h"
namespace chapter15
{
	TextQuery::TextQuery(std::ifstream &infile):file(new std::vector<std::string>)
	{
		std::string text;
		while(getline(infile,text))
		{
			file->push_back(text);
			std::size_t line_number=file->size()-1;
			std::istringstream line(text);
			std::string word;
			while(line>>word)
			{
				std::string key_word;
				for(auto c:word)
				{
					if(!ispunct(c))
						key_word+=c;
				}
				std::shared_ptr<std::set<line_no>> &lines=wm[key_word];
				if(!lines)
					lines.reset(new std::set<line_no>);
				lines->insert(line_number);
			}
		}
	}
	QueryResult TextQuery::query(const std::string &sought) const
	{
		static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
		std::map<std::string,std::shared_ptr<std::set<line_no>>>::const_iterator map_it=wm.find(sought);
		if(map_it==wm.end())
			return QueryResult(sought,nodata,file);
		else
			return QueryResult(sought,map_it->second,file);
	}
	
	std::ostream &print(std::ostream &os,const QueryResult &qr)
	{
		os<<"Executing Query for: "<<qr.sought<<std::endl;
		os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<std::endl;
		for(auto num:*(qr.lines))
			os<<"\t(line "<<num+1<<") "<<*(qr.file->begin()+num)<<std::endl;
		return os;
	}
	QueryResult NotQuery::eval(const TextQuery &text) const
	{
		auto result=query.eval(text);
		auto beg=result.begin(),end=result.end();
		auto ret_lines=std::make_shared<std::set<line_no>>();
		auto sz=result.get_file()->size();
		for(std::size_t n=0;n!=sz;++n)
		{
			if(beg==end||*beg!=n)
				ret_lines->insert(n);
			else if(beg!=end)
				++beg;
		}
		return QueryResult(rep(),ret_lines,result.get_file());
	}
	QueryResult OrQuery::eval(const TextQuery &text) const
	{
		auto left=lhs.eval(text),right=rhs.eval(text);
		auto ret_lines=std::make_shared<std::set<line_no>>(left.begin(),left.end());
		ret_lines->insert(right.begin(),right.end());
		return QueryResult(rep(),ret_lines,left.get_file());
	}
	QueryResult AndQuery::eval(const TextQuery &text) const
	{
		auto left=lhs.eval(text),right=rhs.eval(text);
		auto ret_lines=std::make_shared<std::set<line_no>>();
		set_intersection(left.begin(),left.end(),right.begin(),right.end(),inserter(*ret_lines,ret_lines->begin()));
		return QueryResult(rep(),ret_lines,left.get_file());
	}
}
```
==TextQuery.h==
```
#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <tuple>
namespace chapter10
{
	class TextQuery
	{
	public:
		using line_no=std::vector<std::string>::size_type;
		TextQuery(std::ifstream &);
		std::tuple<std::string,std::shared_ptr<std::set<std::vector<std::string>::size_type>>,std::shared_ptr<std::vector<std::string>>> query(const std::string &) const;
	private:
		std::shared_ptr<std::vector<std::string>> file;
		std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
	};
	inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
	{
	        return (count>1)?word+ending:word;
	}
	std::ostream &print(std::ostream &,const std::tuple<std::string,std::shared_ptr<std::set<std::vector<std::string>::size_type>>,std::shared_ptr<std::vector<std::string>>> &);
}
#endif
```
==TextQuery.cpp==
```
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <memory>
#include "TextQuery.h"
using namespace std;
namespace chapter10
{
	TextQuery::TextQuery(ifstream &infile):file(new vector<string>)
	{
		string text;
		while(getline(infile,text))
		{
			file->push_back(text);
			size_t line_number=file->size()-1;
			istringstream line(text);
			string word;
			while(line>>word)
			{
				shared_ptr<set<line_no>> &lines=wm[word];
				if(!lines)
					lines.reset(new set<line_no>);
				lines->insert(line_number);
			}
		}
	}
	std::tuple<std::string,std::shared_ptr<std::set<std::vector<std::string>::size_type>>,std::shared_ptr<std::vector<std::string>>> TextQuery::query(const string &sought) const
	{
		static shared_ptr<set<line_no>> nodata(new set<line_no>);
		map<string,shared_ptr<set<line_no>>>::const_iterator map_it=wm.find(sought);
		if(map_it==wm.end())
			return tuple(sought,nodata,file);
		else
			return tuple(sought,map_it->second,file);
	}
	std::ostream &print(std::ostream &os,const std::tuple<std::string,std::shared_ptr<std::set<std::vector<std::string>::size_type>>,std::shared_ptr<std::vector<std::string>>> &tp)
	{
		 os<<std::get<0>(tp)<<" occurs "<<std::get<1>(tp)->size()<<" "<<make_plural(std::get<1>(tp)->size(),"time","s")<<std::endl;
	        for(auto num:*(get<1>(tp)))
	                os<<"\t(line "<<num+1<<")"<<*(get<2>(tp)->begin()+num)<<std::endl;
	        return os;
	}
}
```
==test.cpp==
```
#include <fstream>
#include "Query.h"
using namespace std;
using chapter15::Query;
using chapter15::TextQuery;
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	TextQuery text(infile);
	Query q=Query("fiery")&Query("bird")|Query("wind");
	print(cout,q.eval(text));
	return 0;
}
```
### 18.13
需要使用文件作用域或者命名空间作用域的静态变量时可以使用未命名的命名空间。
### 18.14
mathLib::MatrixLib::matrix mathLib::MatrixLib::operator*(const matrix &,const matrix &);
### 18.15
using声明：一次只引入命名空间的一个成员，它的有效范围从using声明的地方开始，到using声音所在作用域结束为止。
using指示：使特定的命名空间中所有的名字都可见，这些名字一般被看作是出现在最近的外层作用域中，如果遇到成员冲突的情况，需要使用作用域运算符指明所需的版本。
### 18.16
#### 位置一
##### using声明
ivar成员冲突
#### 位置二
##### using声明
dvar成员冲突
#### 位置一
##### using指示
`++ivar`这句将有二义性错误
#### 位置二
##### using指示
`++ivar`这句将有二义性错误
### 18.17
1 
```
#include <iostream>	
namespace Exercise
{
	int ivar=0;
	double dvar=0;
	const int limit=1000;
}
int ivar=0;

using Exercise::ivar;
using Exercise::dvar;
using Exercise::limit;

void manip()
{

	double dvar=3.1416;
	int iobj=limit+1;
	++ivar;
	++::ivar;
}
int main(void)
{
	return 0;
}
```
2 
```
#include <iostream>	
namespace Exercise
{
	int ivar=0;
	double dvar=0;
	const int limit=1000;
}
int ivar=0;

void manip()
{

using Exercise::ivar;
using Exercise::dvar;
using Exercise::limit;

	double dvar=3.1416;
	int iobj=limit+1;
	++ivar;
	++::ivar;
}
int main(void)
{
	return 0;
}
```
3 
```
#include <iostream>	
namespace Exercise
{
	int ivar=0;
	double dvar=0;
	const int limit=1000;
}
int ivar=0;

using namespace Exercise;

void manip()
{

	double dvar=3.1416;
	int iobj=limit+1;
	++ivar;
	++::ivar;
}
int main(void)
{
	return 0;
}
```
4 
```
#include <iostream>	
namespace Exercise
{
	int ivar=0;
	double dvar=0;
	const int limit=1000;
}
int ivar=0;


void manip()
{

using namespace Exercise;

	double dvar=3.1416;
	int iobj=limit+1;
	++ivar;
	++::ivar;
}
int main(void)
{
	return 0;
}
```
### 18.18
当mem1是一个string时程序因为更特例化的原因，会调用string中定义的swap版本，而int是内置类型，内置类型没有特定版本的swap，所以会调用std::swap。
### 18.19
如果使用std::swap的形式，则是直接指明调用std命名空间中的swap版本。
### 18.20
- 命名空间primerLib中声明的compte将被加入候选函数集
候选函数`void compute()` `void compute(const void *)` `void compute(int)` `void compute(double,double=3.4)` `void compute(char*,char*=0)`
可行函数
`void compute(const void *)`0能转换成任意指针类型
`void compute(int)`精确匹配
`void compute(double,double=3.4)`int向double的算术类型转换
`void compute(char*,char*=0)`0能转换成任意指针类型
- 如果将using声明置于f函数中compute的调用点之前,将隐藏全局作用域中声明的compute.
候选函数`void compute()` `void compute(const void *)`
可行函数
`void compute(const void *)`0能转换成任意指针类型
### 18.21
