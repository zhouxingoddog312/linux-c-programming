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
### 19.6
这一节的三题用到的Query_base为纯虚函数，AndQuery的构造函数是private的，所以无法构造它们的对象，只能改了改Query.h文件。
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
		Query(std::shared_ptr<Query_base> query):q(query) {}
	private:
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
	public:
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
#endif
```
==test1.cpp==
```
#include <fstream>
#include <memory>
#include "Query.h"
using namespace std;
int main(int argc,char *argv[])
{
	Query a("bird");
	Query b("third");
	Query_base *bp=new AndQuery(a,b);
	if(AndQuery *ap=dynamic_cast<AndQuery *>(bp))
	{
		cout<<"translate successed."<<endl;
	}
	else
		cout<<"translate failed."<<endl;
	return 0;
}
```
### 19.7
==test2.cpp==
```
#include <fstream>
#include <memory>
#include <typeinfo>
#include "Query.h"
using namespace std;
int main(int argc,char *argv[])
{
	Query a("bird");
	Query b("third");
	Query_base *bp=new AndQuery(a,b);
	try
	{
		dynamic_cast<AndQuery &>(*bp);
		cout<<"translate successed."<<endl;
	}
	catch(bad_cast)
	{
		cout<<"translate failed."<<endl;
	}
	return 0;
}
```
### 19.8
==test3.cpp==
```
#include <fstream>
#include <memory>
#include <typeinfo>
#include "Query.h"
using namespace std;
int main(int argc,char *argv[])
{
	Query a("bird");
	Query b("third");
	Query_base *bp=new AndQuery(a,b);
	if(typeid(Query_base)==typeid(*bp))
		cout<<"It's Query_base class."<<endl;
	if(typeid(AndQuery)==typeid(*bp))
		cout<<"It's AndQuery class."<<endl;
	return 0;
}
```
### 19.9
```
#include <iostream>
#include <typeinfo>
#include <string>
#include "19-6/Query.h"
using std::cout;
using std::endl;
using std::string;
int main(void)
{
	int i;
	double d;
	char c;
	string str;
	Query q("hi");
	cout<<typeid(i).name()<<","<<typeid(d).name()<<","<<typeid(c).name()<<","<<typeid(str).name()<<","<<typeid(q).name()<<endl;
	return 0;
}
```
### 19.10
1 A *
2 A *
3 B
### 19.11
指向数据成员的指针的类型除了成员的类型外，还应该包括类的类型。在使用数据成员指针时还需要 提供对象的信息。
### 19.12
==Screen.h==
```
#include <string>
class Screen
{
	public:
		using pos=std::string::size_type;
		Screen()=default;
		Screen(pos ht,pos wd):height{ht},width{wd},contents(ht*wd,' '){}
		Screen(pos ht,pos wd,char c):height{ht},width{wd},contents(ht*wd,c){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const;
		Screen &move(pos r,pos c);
		Screen &set(char);
		Screen &set(pos,pos,char);
		Screen &display(std::ostream &os){do_display(os);return *this;}
		const Screen &display(std::ostream &os) const {do_display(os);return *this;}
		static pos Screen::* data()
		{
			return &Screen::cursor;
		}
	private:
		pos cursor=0,height=0,width=0;
		std::string contents;
		void  do_display(std::ostream &os) const {os<<contents;}
};
inline char Screen::get(pos r,pos c) const
{
	pos row=r*width;
	return contents[row+c];
}
inline Screen &Screen::move(pos r,pos c)
{
	pos row=r*width;
	cursor=row+c;
	return *this;
}
inline Screen &Screen::set(char ch)
{
	contents[cursor]=ch;
	return *this;
}
inline Screen &Screen::set(pos r,pos c,char ch)
{
	contents[r*width+c]=ch;
	return *this;
}
```
==19-12.cpp==
```
#include <iostream>
#include "Screen.h"
int main(void)
{
	Screen scr(5,6,'*');
	scr.move(2,3);
	auto pc=Screen::data();
	std::cout<<scr.*pc<<std::endl;
	return 0;
}
```
### 19.13
`static const std::string Sales_data::* data(){return &Sales_data::bookNo;}`
