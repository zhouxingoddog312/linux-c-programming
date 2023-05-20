[toc]
### 12.1
在此代码结尾，b1包含4个元素，b2超出作用范围，以销毁。
### 12.2
```
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
using namespace std;
class StrBlob
{
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
	void pop_back();
	std::string &front();
	std::string &back();
	const std::string &front() const;
	const std::string &back() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i,const std::string &msg) const;
};
StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
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
```
### 12.3
不需要，因为const StrBlob对象的data数据成员是常量指针，而不是指向常量的指针，所以不管它是否是const，data所指向的vector都可以调用push_back和pop_back。
### 12.4
因为std::vector<std::string>::size_type是无符号类型，它的取值范围是0和正整数。
### 12.5
未编写接受初始化列表参数的显式函数，好处在于，在需要StrBlob的地方可以直接使用列表代替，并且可以直接使用列表对StrBlob对象进行拷贝形式的初始化。
坏处在于，对于接受StrBlob的函数，直接传递一个列表，则会生成一个StrBlob临时量。函数结束时，该临时量被销毁，有可能导致内存泄漏。
### 12.6
```
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
vector<int> *create()
{
	return new vector<int>();
}
vector<int> *scan(istream &is,vector<int> *pivec)
{
	int tmp;
	while(is>>tmp)
		pivec->push_back(tmp);
	return pivec;
}
void print(vector<int> *pivec)
{
	for(const auto &t:*pivec)
		cout<<t<<" ";
	cout<<endl;
	delete pivec;
}
int main(void)
{
	print(scan(cin,create()));
	return 0;
}
```
### 12.7
```
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
shared_ptr<vector<int>> create()
{
	return make_shared<vector<int>>();
}
shared_ptr<vector<int>> scan(istream &is,shared_ptr<vector<int>> pivec)
{
	int tmp;
	while(is>>tmp)
		pivec->push_back(tmp);
	return pivec;
}
void print(shared_ptr<vector<int>> pivec)
{
	for(const auto &t:*pivec)
		cout<<t<<" ";
	cout<<endl;
}
int main(void)
{
	print(scan(cin,create()));
	return 0;
}
```
### 12.8
int型指针可以转换为bool，应该改为`int *p=new (nothrow) int;`这样的话，new分配内存成功时`return p;`会返回true，new分配内存失败时p的值为nullptr，`return p;`会返回false。
### 12.9
`int *q=new int(42),*r=new int(100);`int型指针q指向堆中动态分配的一个初始值为42的int型对象，int型指针r指向堆中动态分配的一个初始值为100的int型对象。
`r=q;`r指向与q相同的对象，而r原先指向的动态分配的内存将无法释放。
`auto q2=make_shared<int>(42),r2=make_shared<int>(100);`shared_ptr\<int\>类对象q2，指向堆中动态分配的一个初始值为42的int型对象。shared_ptr\<int\>类对象r2，指向堆中动态分配的一个初始值为100的int型对象。
`r2=q2;`r2指向与q2相同的对象，而r2的引用计数递减1，变为0，其原先指向的对象会自动释放。
### 12.10
正确，利用智能指针p创建一个临时量，再赋予process的形参ptr，这时候智能指针的引用计数变为2，在函数运行结束后，ptr被销毁，智能指针的引用计数变为1。
### 12.11
这样操作将另一个独立的智能指针也绑定到了get()返回的指针上，由于p和ptr是相互独立创建的，因此各自的引用计数都是1.当process函数结束时，ptr被销毁，这会导致ptr所指向的内存被释放，从而让p成为空悬指针。
### 12.12
- `process(sp)`合法，将智能指针sp赋予形参ptr，引用计数变为2，函数结束，ptr被销毁，引用计数变为1.
- `process(new int())`不合法，接受内置指针类型参数的智能指针构造函数是explicit的，所以无法将一个内置指针隐式转换为一个智能指针，而process函数需要接受一个智能指针参数。
- `process(p)`同上
- `process(shared_ptr<int>(p))`调用合法，但会导致p变为一个空悬指针。操作中利用内置指针p创建一个智能指针临时量赋予形参ptr，在process函数结束时，ptr被销毁，引用计数变为0，其指向的内存会被释放，同时p继续指向（已经释放的）内存。
### 12.13
这样会导致sp变成一个空悬指针，当我们试图使用sp时，将发生未定义的行为，而且当sp被销毁时，它所指向的内存会被第二次delete。
### 12.14
```
#include <iostream>
#include <memory>
using namespace std;
struct destination{};
struct connection{};
connection connect(destination *d)
{
	cout<<"打开连接"<<endl;
	return connection();
}
void disconnect(connection c)
{
	cout<<"关闭连接"<<endl;
}
void end_connection(connection *pc)
{
	disconnect(*pc);
}
void f1(destination &d)
{
	cout<<"f1开始"<<endl;
	connection c=connect(&d);
	cout<<"f1结束"<<endl;
}
void f2(destination &d)
{
	cout<<"f2开始"<<endl;
	connection c=connect(&d);
	shared_ptr<connection> p(&c,end_connection);
	cout<<"f2结束"<<endl;
}
int main(void)
{
	destination d;
	f1(d);
	f2(d);
	return 0;
}
```
### 12.15
```
#include <iostream>
#include <memory>
using namespace std;
struct destination{};
struct connection{};
connection connect(destination *d)
{
	cout<<"打开连接"<<endl;
	return connection();
}
void disconnect(connection c)
{
	cout<<"关闭连接"<<endl;
}
void f1(destination &d)
{
	cout<<"f1开始"<<endl;
	connection c=connect(&d);
	cout<<"f1结束"<<endl;
}
void f2(destination &d)
{
	cout<<"f2开始"<<endl;
	connection c=connect(&d);
	shared_ptr<connection> p(&c,[](connection *pc)->void {disconnect(*pc);});
	cout<<"f2结束"<<endl;
}
int main(void)
{
	destination d;
	f1(d);
	f2(d);
	return 0;
}
```
### 12.16
```
#include <iostream>
#include <memory>
using namespace std;
int main(void)
{
	unique_ptr<int> pi(new int(42));
	unique_ptr<int> pi1(pi);
	return 0;
}
```
### 12.17
- 不合法，unique_ptr不能用int初始化
- 可以通过编译，但是运行时错误，pi不是通过new分配的动态内存，这里又没有重载默认的删除器。所以在p1被销毁时，会调用delete处理pi，发生错误
- 合法，但是需要小心，p2被销毁时会释放其指向的内存，这样会导致pi2变为空悬指针
- 可以通过编译，但是运行时错误，因为没有重载默认的删除器。所以在p3被销毁时，会调用delete处理p3指向的内存，而该内存不是由new分配的动态内存，所以会发生错误
- 合法
- 合法，但是会产生运行时错误。这是因为两个unique_ptr指向同一个对象，其中一个被销毁时另一个会成为空悬指针。两个都被销毁时，指向的内存会被释放两次
### 12.18
unique_ptr的release成员主要用来转移指针的控制权，而shared_ptr只需要普通的赋值或拷贝即可。
### 12.19
```
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
using namespace std;
class StrBlobPtr;
class StrBlob
{
friend class StrBlobPtr;
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
	void pop_back();
	std::string &front();
	std::string &back();
	const std::string &front() const;
	const std::string &back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i,const std::string &msg) const;
};
class StrBlobPtr
{
public:
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	std::string &deref() const;
	StrBlobPtr &incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string &) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr=0;
};

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this,data->size());
}

StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
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
StrBlobPtr & StrBlobPtr::incr()
{
	check(curr,"increment past end of StrBlobPtr");
	++curr;
	return *this;
}
```
### 12.20
```
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
using namespace std;
class StrBlobPtr;
class StrBlob
{
friend class StrBlobPtr;
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
	void pop_back();
	std::string &front();
	std::string &back();
	const std::string &front() const;
	const std::string &back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i,const std::string &msg) const;
};
class StrBlobPtr
{
friend bool equal(const StrBlobPtr &lhs,const StrBlobPtr &rhs);
public:
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	std::string &deref() const;
	StrBlobPtr &incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string &) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr=0;
};

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this,data->size());
}

StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
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
StrBlobPtr & StrBlobPtr::incr()
{
	check(curr,"increment past end of StrBlobPtr");
	++curr;
	return *this;
}
bool equal(const StrBlobPtr &lhs,const StrBlobPtr &rhs)
{
	auto l=lhs.wptr.lock(),r=rhs.wptr.lock();
	if(l==r)
	{
		return (!l||lhs.curr==rhs.curr);
	}
	else
		return false;
}
int main(int argc,char *argv[])
{
	ifstream in(argv[1]);
	string tmp;
	StrBlob store;
	while(getline(in,tmp))
		store.push_back(tmp);
	for(auto p=store.begin();!equal(p,store.end());p.incr())
		cout<<p.deref()<<endl;
	return 0;
}
```
### 12.21
书中的例子，将合法性检查和元素获取分开了，更易读和易修改，但其实两种写法没什么区别。
### 12.22
```
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
using namespace std;
class StrBlobPtr;
class StrBlob
{
friend class StrBlobPtr;
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
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
class StrBlobPtr
{
friend bool equal(const StrBlobPtr &lhs,const StrBlobPtr &rhs);
public:
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	StrBlobPtr(const StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	std::string &deref() const;
	StrBlobPtr &incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string &) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr=0;
};

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
StrBlobPtr & StrBlobPtr::incr()
{
	check(curr,"increment past end of StrBlobPtr");
	++curr;
	return *this;
}
bool equal(const StrBlobPtr &lhs,const StrBlobPtr &rhs)
{
	auto l=lhs.wptr.lock(),r=rhs.wptr.lock();
	if(l==r)
	{
		return (!l||lhs.curr==rhs.curr);
	}
	else
		return false;
}
int main(int argc,char *argv[])
{
	ifstream in(argv[1]);
	string tmp;
	StrBlob store;
	while(getline(in,tmp))
		store.push_back(tmp);
	for(auto p=store.begin();!equal(p,store.end());p.incr())
		cout<<p.deref()<<endl;
	return 0;
}
```
### 12.23
1.
```
#include <iostream>
#include <cstring>
using namespace std;
int main(void)
{
	char str1[]="hello";
	char str2[]="world";
	size_t arrlen=strlen(str1)+strlen(str2)+2;
	char *arr=new char[arrlen];
	strcpy(arr,str1);
	strcpy(arr+strlen(str1)," ");
	strcpy(arr+strlen(arr),str2);
	cout<<arr<<endl;
	delete [] arr;
	return 0;
}
```
2.
```
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main(void)
{
	string str1="hello";
	string str2="world";
	size_t arrlen=str1.size()+str2.size()+2;
	char *arr=new char[arrlen];
	str1=str1+" "+str2;
	for(size_t i=0;i!=str1.size();++i)
		arr[i]=str1[i];
	cout<<arr<<endl;
	delete [] arr;
	return 0;
}
```
### 12.24
```
#include <iostream>
using namespace std;
int main(void)
{
	size_t len;
	cout<<"How many characters:";
	cin>>len;
	char *ps=new char[len+1];
	cin.ignore();
	cin.get(ps,len+1);//对于边长输入，只接收其满足字符数组长度的部分，剩余部分留待继续处理
	cout<<ps;
	delete [] ps;
	return 0;
}
```
### 12.25
`delete [] p`
### 12.26
```
#include <iostream>
#include <memory>
#include <string>
using namespace std;
int main(void)
{
	allocator<string> alloc;
	string s,*ps=alloc.allocate(5);
	string *bg=ps;
	while(cin>>s&&bg!=ps+5)
		alloc.construct(bg++,s);
	const size_t size=bg-ps;
	for(size_t i=0;i!=size;++i)
	{
		cout<<ps[i]<<endl;
		alloc.destroy(ps+i);
	}
	alloc.deallocate(ps,5);
	return 0;
}
```
### 12.27
>TextQuery.h
```
#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <fstream>
#include "QueryResult.h"
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
#endif
```
>TextQuery.cpp
```
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
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
QueryResult TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	map<string,shared_ptr<set<line_no>>>::iterator map_it=wm.find(sought);
	if(map_it==wm.end())
		return QueryResult(sought,nodata,file);
	else
		return QueryResult(sought,map_it->second,file);
}
```
>QueryResult.h
```
#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>
class QueryResult
{
friend std::ostream &print(std::ostream &,const QueryResult &);
public:
	QueryResult(std::string s,std::shared_ptr<std::set<std::vector<std::string>::size_type>> l,std::shared_ptr<std::vector<std::string>> f):sought(s),lines(l),file(f){}
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
#endif
```
>QueryResult.cpp
```
#include <iostream>
#include "QueryResult.h"
std::ostream &print(std::ostream &os,const QueryResult &qr)
{
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<endl;
	for(auto num:*(qr.lines))
		os<<"\t(line "<<num+1<<")"<<*(qr.file->begin()+num)<<endl;
	return os;
}
```
### 12.28
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
int main(int argc,char *argv[])
{
	size_t lines_number=0;
	string tmp,word;
	vector<string> text;
	map<string,set<size_t>> words_lines;
	ifstream infile(argv[1]);
	while(getline(infile,tmp))
	{
		text.push_back(tmp);
		istringstream ln(tmp);
		while(ln>>word)
		{
			words_lines[word].insert(lines_number);
		}
		++lines_number;
	}
	while(1)
	{
		cout<<"Which word do you want to find(q to quit):";
		if(!(cin>>word)||word=="q")
			break;
		const auto p=words_lines.find(word);
		if(p==words_lines.end())
			cout<<"There is no "<<word<<endl;
		else
		{
			cout<<word<<" occurs "<<(p->second).size()<<" times"<<endl;
			for(auto iter=(p->second).cbegin();iter!=(p->second).cend();++iter)
			{
				cout<<"(line "<<*iter+1<<")"<<text[*iter]<<endl;
			}
		}
	}
	return 0;
}
```
### 12.29
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
int main(int argc,char *argv[])
{
	size_t lines_number=0;
	string tmp,word;
	vector<string> text;
	map<string,set<size_t>> words_lines;
	ifstream infile(argv[1]);
	while(getline(infile,tmp))//这里如果要改成do while的模式的话，得在前面先getline，进入循环后又要判断一次读入结果，繁琐得多
	{
		text.push_back(tmp);
		istringstream ln(tmp);
		while(ln>>word)
		{
			words_lines[word].insert(lines_number);
		}
		++lines_number;
	}
	do//这里改成do while没有什么影响
	{
		cout<<"Which word do you want to find(q to quit):";
		if(!(cin>>word)||word=="q")
			break;
		const auto p=words_lines.find(word);
		if(p==words_lines.end())
			cout<<"There is no "<<word<<endl;
		else
		{
			cout<<word<<" occurs "<<(p->second).size()<<" times"<<endl;
			for(auto iter=(p->second).cbegin();iter!=(p->second).cend();++iter)
			{
				cout<<"(line "<<*iter+1<<")"<<text[*iter]<<endl;
			}
		}
	}
	while(1);
	return 0;
}
```
### 12.30
```
#include <iostream>
#include <fstream>
#include "12-27/TextQuery.h"
#include "12-27/QueryResult.h"
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
### 12.31
我认为时set更方便，因为vector不会维护元素的序，所以输出时需要另外的操作。同时，vector不保证关键字不重复，这又需要另外的操作。
### 12.32
StrBlob.h
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
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
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
class StrBlobPtr
{
public:
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	StrBlobPtr(const StrBlob &a,std::size_t sz=0):wptr(a.data),curr(sz){}
	std::string &deref() const;
	StrBlobPtr &incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string &) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr=0;
};
#endif
```
StrBlob.cpp
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
StrBlobPtr & StrBlobPtr::incr()
{
	check(curr,"increment past end of StrBlobPtr");
	++curr;
	return *this;
}
```
TextQuery.h
```
#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include "QueryResult.h"
#include "StrBlob.h"
class TextQuery
{
public:
	using line_no=std::vector<std::string>::size_type;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;
private:
	StrBlob file;
	std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
};
#endif
```
TextQuery.cpp
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
TextQuery::TextQuery(ifstream &infile)
{
	string text;
	while(getline(infile,text))
	{
		file.push_back(text);
		size_t line_number=file.size()-1;
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
QueryResult TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	map<string,shared_ptr<set<line_no>>>::const_iterator map_it=wm.find(sought);
	if(map_it==wm.end())
		return QueryResult(sought,nodata,file);
	else
		return QueryResult(sought,map_it->second,file);
}
```
QueryResult.h
```
#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include "StrBlob.h"
class QueryResult
{
friend std::ostream &print(std::ostream &,const QueryResult &);
public:
	QueryResult(std::string s,std::shared_ptr<std::set<std::vector<std::string>::size_type>> l,StrBlob f):sought(s),lines(l),file(f){}
private:
	std::string sought;
	std::shared_ptr<std::set<std::vector<std::string>::size_type>> lines;
	StrBlob file;
};
std::ostream &print(std::ostream &,const QueryResult &);
inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
{
	return (count>1)?word+ending:word;
}
#endif
```
QueryResult.cpp
```
#include <iostream>
#include "QueryResult.h"
std::ostream &print(std::ostream &os,const QueryResult &qr)
{
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<std::endl;
	auto p=qr.file.begin();
	auto index=0;
	for(auto num:*(qr.lines))
	{
		os<<"\t(line "<<num+1<<")";
		for(auto mk=num-index;mk!=0;--mk,++index)
			p.incr();
		os<<p.deref()<<std::endl;
	}
	return os;
}
```
test.cpp
```
#include <iostream>
#include <fstream>
#include "TextQuery.h"
#include "QueryResult.h"
#include "StrBlob.h"
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
### 12.33
QueryResult.h
```
#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>
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
#endif
```
QueryReuslt.cpp
```
#include <iostream>
#include "QueryResult.h"
std::ostream &print(std::ostream &os,const QueryResult &qr)
{
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<std::endl;
	for(auto num:*(qr.lines))
		os<<"\t(line "<<num+1<<")"<<*(qr.file->begin()+num)<<std::endl;
	return os;
}
```
