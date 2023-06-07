[toc]
### 13.1
如果一个构造函数的第一个参数是自身类类型的引用，且任何额外参数都有默认值，则此构造函数是拷贝构造函数。拷贝构造函数用于类类型的拷贝初始化。在以下情形中会发生类类型的拷贝初始化：
- 使用=定义变量时
- 将一个对象作为实参传递给一个非引用类型的形参
- 从一个返回类型为非引用类型的函数返回一个对象
- 用花括号列表初始化一个数组中的元素或一个聚合类中的成员
### 13.2
拷贝构造函数的第一个参数必须时自身类类型的引用，否则为了调用拷贝构造函数，我们必须拷贝它的实参，但为了拷贝实参，我们又需要调用拷贝构造函数，如此无线循环，调用就不会成功。
### 13.3
StrBlob和StrBlobPtr都没有定义自己的拷贝构造函数，编译器会为它们合成拷贝构造函数，合成的拷贝构造函数会将其参数的成员逐个拷贝到正在创建的对象中。StrBlob只有一个shared_ptr类型的数据成员，调用其拷贝构造函数，其引用计数加一。而StrBlobPtr有一个weak_ptr类型的数据成员，调用其拷贝构造函数，引用计数不增加。其size_t类型的数据成员直接拷贝。
### 13.4
`Point foo_bar(Point arg)`为非引用类型的形参传值，及为非引用类型的返回类型返回对象。
`Point local=arg`使用=进行拷贝初始化。
`*heap=local`使用=进行拷贝初始化。
`Point pa[4]={local,*heap}`用花括号列表初始化一个数组中的元素
### 13.5
```
class HasPtr
{
public:
	HasPtr(const std::string &s=std::string()):ps(new std::string(s)),i(0) {}
	HasPtr(const HasPtr &OHasPtr):ps(new std::string(*(OHasPtr.ps))),i(OHasPtr.i) {}
private:
	std::string *ps;
	int i;
}
```
### 13.6
- 拷贝赋值运算符本身是一个重载的赋值运算符，定义为类的成员函数，左侧运算对象绑定到隐含的this参数，右侧运算对象接受一个与其所在类相同类型的参数。通常返回一个指向其左侧运算对象的引用。
- 类的对象赋值时使用其定义的拷贝赋值运算符。
- 用来禁止该类型对象的赋值，或者将右侧运算对象的每个非static成员赋予左侧运算对象的对应成员。
- 如果一个类未定义自己的拷贝赋值运算符，编译器会为它生成一个合成拷贝赋值运算符。
### 13.7
StrBlob和StrBlobPtr都没有定义自己的拷贝赋值运算符，编译器会为它们生成一个合成拷贝赋值运算符。两个StrBlob类型对象之间赋值，则会将右侧对象的shared_ptr成员赋值给左侧对象的shared_ptr成员，左侧对象的shared_ptr成员引用计数减一，右侧加一。两个StrBlobPtr类型对象之间赋值，则会将右侧对象的weak_ptr成员赋值给左侧对象的weak_ptr成员，再将右侧对象的size_t成员赋值给左侧对象的size_t类型成员，并返回左侧对象的引用。
### 13.8
```
class HasPtr
{
public:
	HasPtr(const std::string &s=std::string()):ps(new std::string(s)),i(0) {}
	HasPtr(const HasPtr &OHasPtr):ps(new std::string(*(OHasPtr.ps))),i(OHasPtr.i) {}
	HasPtr & operator=(const HasPtr &rhs) {std::string *newps=new std::string(*rhs.ps);delete ps;ps=newps;i=rhs.i;return *this;}
private:
	std::string *ps;
	int i;
}
```
### 13.9
- 析构函数用来释放对象使用的资源，并销毁对象得非static数据成员。
- 合成析构函数要嘛被用来阻止该类型的对象被销毁，要嘛函数体为空，在函数体之后进行析构阶段销毁对象非static数据成员。
- 当一个类未定义自己的析构函数时，编译器会为它定义一个合成析构函数。
### 13.10
- StrBlob类未定义自己的析构函数，所以编译器会为它定义一个合成析构函数，该函数的函数体为空。StrBlob类型对象销毁时，在执行完空的函数体后会进行析构阶段，这时会调用shared_ptr类型数据成员自己的析构函数。
- StrBlobPtr类未定义自己的析构函数，所以编译器会为它定义一个合成的析构函数，该函数的函数体为空。StrBlobPtr类型对象销毁时，在执行完空的函数体后会进行析构阶段，这时curr成员为内置类型，什么也不做。再依次执行weak_ptr与shared_ptr的析构函数。
### 13.11
```
class HasPtr
{
public:
	HasPtr(const std::string &s=std::string()):ps(new std::string(s)),i(0) {}
	HasPtr(const HasPtr &OHasPtr):ps(new std::string(*(OHasPtr.ps))),i(OHasPtr.i) {}
	HasPtr & operator=(const HasPtr &rhs) {std::string *newps=new std::string(*rhs.ps);delete ps;ps=newps;i=rhs.i;return *this;}
	~HasPtr() {delete ps;}
private:
	std::string *ps;
	int i;
}
```
### 13.12
会发生3次析构函数的调用，代码块结束时四个局部变量都离开了其作用域，将会被销毁。但trans是内置指针类型，销毁它时什么都不会做，自然也就不会调用Sales_data的析构函数。
### 13.13
```
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
class X
{
public:
	X() {std::cout<<"X()"<<std::endl;}
	X(const X &) {std::cout<<"X(const X &)"<<std::endl;}
	X & operator=(const X &) {std::cout<<"X=X"<<std::endl;return *this;}
	~X() {std::cout<<"~X()"<<std::endl;}
private:
};
void f1(X x) {}
void f2(X &x) {}
int main(void)
{
    cout << "局部变量：" << endl;
    X x;
    cout << endl;

    cout << "非引用参数传递：" << endl;
    f1(x);
    cout << endl;

    cout << "引用参数传递：" << endl;
    f2(x);
    cout << endl;

    cout << "动态分配：" << endl;
    X *px = new X;
    cout << endl;

    cout << "添加到容器中：" << endl;
    vector<X> vx;
    vx.push_back(x);
    cout << endl;

    cout << "释放动态分配对象：" << endl;
    delete px;
    cout << endl;

    cout << "拷贝初始化和赋值：" << endl;
    X y = x;
    y = x;
    cout << endl;

    cout << "程序结束！" << endl;
    return 0;
}
```
### 13.14
代码将输出三个相同的序号，因为合成的拷贝构造函数简单的将序号复制，这三个对象的需要都将等于对象a创建时的序号。
```
#include <iostream>
unsigned idx=0;
class numbered
{
friend void f(numbered s);
public:
	numbered():mysn(idx++) {}
private:
	unsigned mysn=0;
};
using std::cout;
using std::endl;
void f(numbered s)
{
	cout<<s.mysn<<endl;
}
int main(void)
{
	numbered a,b=a,c=b;
	f(a);
	f(b);
	f(c);
	return 0;
}
```
### 13.15
可以改变上一题中调用的输出结果，`b=a`以及`c=b`都将调用拷贝构造函数为对象生成唯一的序号。而在调用函数f的过程中，由于对象作为实参传递给非引用类型的形参，又会调用拷贝构造函数为函数的局部对象生成唯一的序号。
```
#include <iostream>
unsigned idx=0;
class numbered
{
friend void f(numbered s);
public:
	numbered():mysn(idx++) {}
	numbered(const numbered &ori_num):mysn(idx++) {}
private:
	unsigned mysn=0;
};
using std::cout;
using std::endl;
void f(numbered s)
{
	cout<<s.mysn<<endl;
}
int main(void)
{
	numbered a,b=a,c=b;
	f(a);
	f(b);
	f(c);
	return 0;
}
```
### 13.16
会改变输出结果，在调用函数f时就不会再调用numbered类型对象的拷贝构造函数，输出的就是分别a、b、c的序号数据成员。
```
#include <iostream>
unsigned idx=0;
class numbered
{
friend void f(const numbered &s);
public:
	numbered():mysn(idx++) {}
	numbered(const numbered &ori_num):mysn(idx++) {}
private:
	unsigned mysn=0;
};
using std::cout;
using std::endl;
void f(const numbered &s)
{
	cout<<s.mysn<<endl;
}
int main(void)
{
	numbered a,b=a,c=b;
	f(a);
	f(b);
	f(c);
	return 0;
}
```
### 13.17
如上。
### 13.18
```
class Employee
{
public:
	Employee():unique_sn(sn++) {}
	Employee(const std::string &str):name(str),unique_sn(sn++) {}
private:
	std::string name;
	unsigned unique_sn;
	static unsigned sn;
};
unsigned Employee::sn=0;
```
### 13.19
Employee类需要自己的拷贝控制成员，因为合成的拷贝构造函数和拷贝赋值运算符只会直接拷贝雇员证号数据成员。
```
class Employee
{
public:
	Employee():unique_sn(sn++) {}
	Employee(const std::string &str):name(str),unique_sn(sn++) {}
	Employee(const Employee &rhs):name(rhs.name),unique_sn(sn++) {}
	Employee & operator=(const Employee &rhs) {name=rhs.name;return *this;}
	~Employee() {}
private:
	std::string name;
	unsigned unique_sn;
	static unsigned sn;
};
unsigned Employee::sn=0;
```
### 13.20
TextQuery和QueryResult类都未定义自己的拷贝控制成员，所以它们都会使用合成的版本，在合成版本的拷贝控制成员中，这两个类的shared_ptr、map、string类型的数据成员都会调用它们自己的拷贝控制成员完成拷贝、赋值、销毁的工作。
### 13.21
TextQuery和QueryResult类的数据成员都是标准库类型，它们都定义有设计良好的拷贝控制成员，用合成的拷贝控制成员即可方便的管理这两个类型。所以它们不需要定义自己版本的拷贝控制成员。
### 13.22
```
class HasPtr
{
	public:
		HasPtr(const std::string &s=std::string()):pts(new std::string(s)) {}
		HasPtr(const HasPtr &org):value(org.value),pts(new std::string(*org.pts)) {}
		HasPtr & operator=(const HasPtr &rhs) {std::string *tmp=new std::string(*rhs.pts);delete pts;pts=tmp;value=rhs.value;return *this;}
		~HasPtr() {delete pts;}
	private:
		int value=0;
		std::string *pts;
};
```
### 13.23
如上
### 13.24
未定义析构函数则无法释放指针数据成员所管理的内存，造成内存泄漏。未定义拷贝构造函数，则会简单的复制指针数据成员，使生成的新对象与原对象的指针数据成员指向同一个string。
### 13.25
拷贝构造函数以及拷贝赋值运算符需要使用原对象的data成员所指向的vector初始化被构造以及被赋值对象的data成员，如此可以复制该vector而不是拷贝shared_ptr成员。因为StrBlob类中只有一个shared_ptr类的数据成员，它有设计良好的析构函数，所以合成的析构函数可以顺利的完成相应工作。
### 13.26
==StrBlob.h==
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
	
	StrBlob(const StrBlob &);
	StrBlob & operator=(const StrBlob &);

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
### 13.27
```
class HasPtr
{
	public:
		HasPtr(const std::string &s=std::string()):pts(new std::string(s)),value(0),use(new std::size_t(1)) {}
		HasPtr(const HasPtr &org):pts(org.pts),value(org.value),use(org.use) {++*use;}
		HasPtr & operator=(const HasPtr &rhs);
		~HasPtr();
	private:
		std::string *pts;
		int value;
		std::size_t *use;
};
HasPtr & HasPtr::operator=(const HasPtr &rhs)
{
	++*rhs.use;
	if(--*use==0)
	{
		delete pts;
		delete use;
	}
	pts=rhs.pts;
	value=rhs.value;
	use=rhs.use;
	return *this;
}
HasPtr::~HasPtr()
{
	if(--*use)
	{
		delete pts;
		delete use;
	}
}
```
### 13.28
```
class TreeNode
{
	public:
		TreeNode():count(1),left(nullptr),right(nullptr) {}
		TreeNode(const std::string &str=std::string(),TreeNode *lchild=nullptr,TreeNode *rchild=nullptr):value(str),count(1),left(lchild),right(rchild) {}
		void CopyTree();
		int ReleaseTree();
		TreeNode(const TreeNode &);
		~TreeNode();
	private:
		std::string value;
		int count;
		TreeNode *left;
		TreeNode *right;
};
class BinStrTree
{
	public:
		BinStrTree():root(nullptr) {}
		BinStrTree(TreeNode *tree=nullptr):root(tree) {}
		BinStrTree(const BinStrTree &);
		~BinStrTree();
	private:
		TreeNode *root;
};
BinStrTree::BinStrTree(const BinStrTree &org):root(org.root)
{
	root->CopyTree();
}
BinStrTree::~BinStrTree()
{
	if(!root->ReleaseTree())
		delete root;
}

void TreeNode::CopyTree()
{
	if(left)
		left->CopyTree();
	if(right)
		right->CopyTree();
	++count;
}
int TreeNode::ReleaseTree()
{
	if(left)
	{
		if(!left->ReleaseTree())
			delete left;
	}
	if(right)
	{
		if(!right->ReleaseTree())
			delete  right;
	}
	--count;
	return count;
}
TreeNode::TreeNode(const TreeNode &org):value(org.value),count(1),left(org.left),right(org.right)
{
	if(left)
		left->CopyTree();
	if(right)
		right->CopyTree();
}
TreeNode::~TreeNode()
{
	if(count)
		ReleaseTree();
}
```
### 13.29
`swap(HasPtr &,HasPtr &)`中所调用的swap是属于标准库的std::swap版本，所以不会导致递归。
### 13.30
```
#include <iostream>
#include <string>
class HasPtr
{
	friend void swap(HasPtr &,HasPtr &);
	friend void print(const HasPtr &);
	public:
		HasPtr(const std::string &s=std::string()):pts(new std::string(s)) {}
		HasPtr(const HasPtr &org):value(org.value),pts(new std::string(*org.pts)) {}
		HasPtr & operator=(const HasPtr &rhs) {std::string *tmp=new std::string(*rhs.pts);delete pts;pts=tmp;value=rhs.value;return *this;}
		~HasPtr() {delete pts;}
	private:
		int value=0;
		std::string *pts;
};
void swap(HasPtr &lhs,HasPtr &rhs)
{
	using std::swap;
	swap(lhs.value,rhs.value);
	swap(lhs.pts,rhs.pts);
	std::cout<<"swap complete."<<std::endl;
}
void print(const HasPtr &hp)
{
	std::cout<<*hp.pts<<std::endl;
}
int main(void)
{
	HasPtr a("s1"),b("s2");
	swap(a,b);
	std::cout<<"a"<<std::endl;
	print(a);
	std::cout<<"b"<<std::endl;
	print(b);
	return 0;
}
```
### 13.31
```
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
class HasPtr
{
	friend void swap(HasPtr &,HasPtr &);
	friend std::ostream & print(std::ostream &,const HasPtr &);
	public:
		HasPtr(const std::string &s=std::string()):pts(new std::string(s)) {}
		HasPtr(const HasPtr &org):value(org.value),pts(new std::string(*org.pts)) {}
		HasPtr & operator=(const HasPtr &rhs) {std::string *tmp=new std::string(*rhs.pts);delete pts;pts=tmp;value=rhs.value;return *this;}
		bool operator<(const HasPtr &rhs) const {return *pts<*rhs.pts;}
		~HasPtr() {delete pts;}
	private:
		int value=0;
		std::string *pts;
};
inline void swap(HasPtr &lhs,HasPtr &rhs)
{
	using std::swap;
	swap(lhs.value,rhs.value);
	swap(lhs.pts,rhs.pts);
	std::cout<<"swap complete."<<std::endl;
}
std::ostream & print(std::ostream &os,const HasPtr &hp)
{
	os<<*hp.pts<<std::endl;
	return os;
}
using std::vector;
using std::cout;
using std::string;
int main(void)
{
	vector<HasPtr> hpv;
	string s="z y x a c d e f i h j k o q p r t s n m l";
	for(auto str:s)
		hpv.push_back(HasPtr(string("")+str));
	for(auto pv:hpv)
		print(cout,pv);
	sort(hpv.begin(),hpv.end());
	for(auto pv:hpv)
		print(cout,pv);
	return 0;
}
```
### 13.32
类指针的HasPtr版本不会分配新的string副本，所以不需要自己的swap函数。
