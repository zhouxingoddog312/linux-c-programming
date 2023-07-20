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
