[toc]

### 19.1
```
#include <cstdlib>
#include <memory>
using std::bad_alloc;
void * operator new(size_t size)
{
	if(void *result=malloc(size))
		return result;
	else
		throw bad_alloc();
}
void operator delete(void *mem) noexcept
{
	free(mem);
}
```
### 19.2
==StrVec.h==
```
#ifndef _STRVEC_H
#define _STRVEC_H
#include <string>
#include <cstddef>
#include <utility>
#include <memory>
#include <initializer_list>
void *operator new(size_t);
void operator delete(void *) noexcept;
class StrVec
{
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
		StrVec(const StrVec &);
		StrVec(StrVec &&s) noexcept :elements(s.elements),first_free(s.first_free),cap(s.cap) {s.elements=s.first_free=s.cap=nullptr;}
		StrVec(std::initializer_list<std::string>);
		StrVec & operator=(const StrVec &);
		StrVec & operator=(StrVec &&) noexcept;
		~StrVec() {free();}
		void push_back(const std::string &);
		void push_back(std::string &&);
		size_t size() {return first_free-elements;}
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
#endif
```
==StrVec.cpp
```
#include "StrVec.h"
#include <cstdlib>
#include <memory>
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
StrVec & StrVec::operator=(StrVec &&s) noexcept
{
	if(this!=&s)
	{
		free();
		elements=s.elements;
		first_free=s.first_free;
		cap=s.cap;
		s.elements=s.first_free=s.cap=nullptr;
	}
	return *this;
}
void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++,s);
}
void StrVec::push_back(std::string &&s)
{
	chk_n_alloc();
	alloc.construct(first_free++,std::move(s));
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
void * operator new(size_t size)
{
	if(void *result=malloc(size))
		return result;
	else
		throw std::bad_alloc();
}
void operator delete(void *mem) noexcept
{
	free(mem);
}
```
### 19.3
1 成功，因为pa的类型是目标类型的公有基类。
2 失败，因为pb实际指向B类型而非目标C类型。
3 失败，因为A是D的一个二义基类。
```
#include <iostream>
#include <memory>
class A
{
	public:
		A()=default;
		virtual ~A()=default;
};
class B:public A
{
	public:
		B()=default;
		virtual ~B()=default;
};
class C:public B
{
	public:
		C()=default;
		virtual ~C()=default;
};
class D:public B,public A
{
	public:
		D()=default;
		virtual  ~D()=default;
};
int main(void)
{
//	A *pa=new C;
//	B *pb=dynamic_cast<B *>(pa);
	B *pb=new B;
	if(C *pc=dynamic_cast<C *>(pb))
		std::cout<<"yes"<<std::endl;
	else
		std::cout<<"no"<<std::endl;
//	A *pa=new D;
//	B *pb=dynamic_cast<B *>(pa);
	return 0;
}
```
### 19.4
```
#include <iostream>
#include <memory>
class A
{
	public:
		A()=default;
		virtual ~A()=default;
};
class B:public A
{
	public:
		B()=default;
		virtual ~B()=default;
};
class C:public B
{
	public:
		C()=default;
		virtual ~C()=default;
};
class D:public B,public A
{
	public:
		D()=default;
		virtual  ~D()=default;
};
int main(void)
{
//运行时会抛出错误
	A *pa=new A;
	try
	{
		C &rc=dynamic_cast<C &>(*pa);
	}
	catch(std::bad_cast err)
	{
		std::cerr<<err.what()<<std::endl;
	}
	return 0;
}
```
### 19.5
想要使用基类的引用或指针使用派生类的非虚函数操作的时候。
