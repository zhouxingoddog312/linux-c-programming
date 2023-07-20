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
