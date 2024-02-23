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
### 19.14
`auto pmf=&Screen::get_cursor;`合法，pmf是一个成员函数指针，它指向Screen类的常量成员函数，该函数不接受参数，返回一个char类型数据.
`pmf=&Screen::get`合法，pmf被赋值为Screen类内不接受参数并返回char类型值的那个get成员函数。
### 19.15
指向成员函数的指针的类型包含所指向的类的类型，并且在调用时需要提供类的对象，同时指向成员函数的指针和成员函数名之间不存在自动转换规则。
### 19.16
`using avp=double (Sales_data::*) () const`
### 19.17
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
/*在这里*/
using p1=char (Sales_data::*) () const;
using p2=char (Sales_data::*) (Screen::pos,Screen::pos) const;
using p3=Screen & (Sales_data::*) (Screen::pos,Screen::pos);
using p4=Screen & (Sales_data::*) (char);
using p5=Screen & (Sales_data::*) (Screen::pos,Screen::pos,char);
using p6=Screen & (Sales_data::*) (std::ostream &);
using p7=const Screen & (Sales_data::*) (std::ostream &) const;
using p8=void (Sales_data::*) (std::ostream &) const;
/********/
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
### 19.18
```
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::placeholders::_1;
int main(void)
{
	vector<string> svec={"hi","","","hello",""};
	cout<<count_if(svec.begin(),svec.end(),bind(&string::empty,_1))<<endl;
	return 0;
}
```



### 19.20
==19-20.cpp==
```
#include <iostream>
#include <fstream>
#include "TextQuery.h"
using namespace std;
void runQueries(ifstream &infile)
{
	TextQuery tq(infile);
	while(true)
	{
		cout<<"enter word to look for, or q to quit:";
		string s;
		if(!(cin>>s)||s=="q")
			break;
		print(cout,tq.query(s))<<endl;
	}
}
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	runQueries(infile);
	return 0;
}
```
==TextQuery.h==
```
#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
class TextQuery
{
public:
	class QueryResult;
	using line_no=std::vector<std::string>::size_type;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
};
class TextQuery::QueryResult
{
	friend std::ostream &print(std::ostream &,const QueryResult &);
	public:
		QueryResult(std::string s,std::shared_ptr<std::set<std::vector<std::string>::size_type>> l,std::shared_ptr<std::vector<std::string>> f):sought(s),lines(l),file(f){}
	private:
		std::string sought;
		std::shared_ptr<std::set<std::vector<std::string>::size_type>> lines;
		std::shared_ptr<std::vector<std::string>> file;
};
std::ostream &print(std::ostream &,const TextQuery::QueryResult &);
inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
{
	return (count>1)?word+ending:word;
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
TextQuery::QueryResult TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	map<string,shared_ptr<set<line_no>>>::const_iterator map_it=wm.find(sought);
	if(map_it==wm.end())
		return QueryResult(sought,nodata,file);
	else
		return QueryResult(sought,map_it->second,file);
}

std::ostream &print(std::ostream &os,const TextQuery::QueryResult &qr)
{
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<std::endl;
	for(auto num:*(qr.lines))
		os<<"\t(line "<<num+1<<")"<<*(qr.file->begin()+num)<<std::endl;
	return os;
}
```
### 19.21
<a id="1">token.h</a>
```
#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include "Sales_data.h"
using std::string;
class Token
{
	friend std::ostream & operator<<(std::ostream &,const Token &);
	public:
		Token():tok(INT),ival(0) {}
		Token(const Token &t):tok(t.tok) {copyUnion(t);}
		Token(Token &&t):tok(std::move(t.tok)) {moveUnion(std::move(t));}
		~Token()
		{
			if(tok==STR)
				sval.~string();
			else if(tok==SAL)
				salval.~Sales_data();
		}
		Token & operator=(const Token &);
		Token & operator=(Token &&);
		Token & operator=(const std::string &);
		Token & operator=(const Sales_data &);
		Token & operator=(int);
		Token & operator=(char);
		Token & operator=(double);
	private:
		enum {INT,CHAR,DBL,STR,SAL} tok;
		union
		{
			int ival;
			char cval;
			double dval;
			std::string sval;
			Sales_data salval;
		};
		void copyUnion(const Token &);
		void moveUnion(Token &&);
		void free()
		{
			if(tok==STR)
				sval.~string();
			if(tok==SAL)
				salval.~Sales_data();
		}
};
std::ostream & operator<<(std::ostream &,const Token &);
#endif
```
==token.cpp==
```
#include "token.h"
void Token::copyUnion(const Token &t)
{
	switch(tok)
	{
		case Token::INT:
			ival=t.ival;
			break;
		case Token::CHAR:
			cval=t.cval;
			break;
		case Token::DBL:
			dval=t.dval;
			break;
		case Token::STR:
			new (&sval) std::string(t.sval);
			break;
		case Token::SAL:
			new (&salval) Sales_data(t.salval);
			break;
	}
}
void Token::moveUnion(Token &&t)
{
	switch(tok)
	{
		case Token::INT:
			ival=t.ival;
			break;
		case Token::CHAR:
			cval=t.cval;
			break;
		case Token::DBL:
			dval=t.dval;
			break;
		case Token::STR:
			new (&sval) std::string(std::move(t.sval));
			break;
		case Token::SAL:
			new (&salval) Sales_data(std::move(t.salval));
			break;
	}
}
Token & Token::operator=(int i)
{
	if(tok==STR)
		sval.~string();
	if(tok==SAL)
		salval.~Sales_data();
	tok=INT;
	ival=i;
	return *this;
}
Token & Token::operator=(char ch)
{
	if(tok==STR)
		sval.~string();
	if(tok==SAL)
		salval.~Sales_data();
	tok=CHAR;
	cval=ch;
	return *this;
}
Token & Token::operator=(double d)
{
	if(tok==STR)
		sval.~string();
	if(tok==SAL)
		salval.~Sales_data();
	tok=DBL;
	dval=d;
	return *this;
}
Token & Token::operator=(const std::string &str)
{
	if(tok==STR)
		sval=str;
	else if(tok==SAL)
	{
		salval.~Sales_data();
		tok=STR;
		new (&sval) std::string(str);
	}
	else
	{
		tok=STR;
		new (&sval) std::string(str);
	}
	return *this;
}
Token & Token::operator=(const Sales_data &sales)
{
	if(tok==SAL)
		salval=sales;
	else if(tok==STR)
	{
		sval.~string();
		tok=SAL;
		new (&salval) Sales_data(sales);
	}
	else
	{
		tok=SAL;
		new (&salval) Sales_data(sales);
	}
	return *this;
}
Token & Token::operator=(const Token &t)
{
	switch(tok)
	{
		case Token::STR:
			if(t.tok==STR)
				sval=t.sval;
			else
			{
				sval.~string();
				tok=t.tok;
				copyUnion(t);
			}	
			break;
		case Token::SAL:
			if(t.tok==SAL)
				salval=t.salval;
			else
			{
				salval.~Sales_data();
				tok=t.tok;
				copyUnion(t);
			}
			break;
		default:
			tok=t.tok;
			copyUnion(t);
	}
	return *this;
}
Token & Token::operator=(Token &&t)
{
	if(this!=&t)
	{
		free();
		tok=std::move(t.tok);
		moveUnion(std::move(t));
	}
	return *this;
}
std::ostream & operator<<(std::ostream &os,const Token &t)
{
	switch(t.tok)
	{
		case Token::INT:
			std::cout<<t.ival;
			break;
		case Token::CHAR:
			std::cout<<t.cval;
			break;
		case Token::DBL:
			std::cout<<t.dval;
			break;
		case Token::STR:
			std::cout<<t.sval;
			break;
		case Token::SAL:
			std::cout<<t.salval;
			break;
	}
	return os;
}
```
==Sales_data.h==
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
		double avg_price() const;
	private:
		std::string bookNo;
		unsigned units_sold=0;
		double revenue=0.0;
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
### 19.22
[见19.21](#1)
### 19.23
[见19.21](#1)
### 19.24
不会出错
### 19.25
[见19.21](#1)
==test.cpp==
```
#include <iostream>
#include <string>
#include "token.h"
int main(void)
{
	Token t;
	t=1;
	std::cout<<t<<std::endl;
	t='c';
	std::cout<<t<<std::endl;
	t=1.314;
	std::cout<<t<<std::endl;
	t="hello";
	std::cout<<t<<std::endl;
	t=Sales_data("10212x",3,24);
	std::cout<<t<<std::endl;
	return 0;
}
```
### 19.26
```
extern "C" int compute(int *,int);//这是一个C函数，它接受两个参数int *以及int，返回int
extern "C" double compute(double *,double);//这是一个C函数，它接受两个参数double *以及double，返回double
```
不合法，因为C语言不支持函数重载，这两个函数的名字相同了。

