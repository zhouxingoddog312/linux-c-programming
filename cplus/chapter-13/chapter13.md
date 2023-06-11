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
### 13.33
因为首先我们要将Folder的指针存入Message的folders数据成员中，那么形参就不能是Folder，而应该是Folder的引用或指针。而save和remove函数中调用了Folder的addMsg和remMsg成员函数，这将改变Folder的数据成员，所以不能是const的。
### 13.34
<a id="1">Message.h</a>
```
#ifndef _MESSAGE_H
#define _MESSAGE_H
#include <string>
#include <set>
class Folder;
class Message
{
	friend class Folder;
	friend void swap(Message &,Message &);
	public:
		explicit Message(const std::string &str=""):contents(str) {}
		Message(const Message &);
		Message & operator=(const Message &);
		~Message();
		void save(Folder &);
		void remove(Folder &);
	private:
		std::string contents;
		std::set<Folder *> folders;
		void add_to_Folders(const Message &);
		void remove_from_Folders();
		void addfolder(Folder *f) {folders.insert(f);}
		void remfolder(Folder *f) {folders.erase(f);}
};
class Folder
{
	friend void swap(Message &,Message &);
	friend class Message;
	public:
		Folder()=default;
		Folder(const Folder &f):messages(f.messages) {add_to_Messages(f);}
		Folder & operator=(const Folder &);
		~Folder();
		void save(Message &);
		void remove(Message &);
	private:
		std::set<Message *> messages;
		void addMsg(Message *m) {messages.insert(m);}
		void remMsg(Message *m) {messages.erase(m);}
		void add_to_Messages(const Folder &);
		void remove_from_Messages();
};
#endif
```
==Message.cpp==
```
#include "Message.h"
void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}
void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}
void Message::add_to_Folders(const Message &m)
{
	for(auto f:m.folders)
		f->addMsg(this);
}
void Message::remove_from_Folders()
{
	for(auto f:folders)
		f->remMsg(this);
}
Message::Message(const Message &m):contents(m.contents),folders(m.folders)
{
	add_to_Folders(m);
}
Message & Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents=rhs.contents;
	folders=rhs.folders;
	add_to_Folders(rhs);
	return *this;
}
Message::~Message()
{
	remove_from_Folders();
}
void swap(Message &lhs,Message &rhs)
{
	using std::swap;
	for(auto f:lhs.folders)
		f->remMsg(&lhs);
	for(auto f:rhs.folders)
		f->remMsg(&rhs);
	swap(lhs.contents,rhs.contents);
	swap(lhs.folders,rhs.folders);
	for(auto f:lhs.folders)
		f->addMsg(&lhs);
	for(auto f:rhs.folders)
		f->addMsg(&rhs);
}



void Folder::add_to_Messages(const Folder &f)
{
	for(auto m:f.messages)
		m->addfolder(this);
}
void Folder::remove_from_Messages()
{
	for(auto m:messages)
		m->folders.erase(this);
}
void Folder::save(Message &m)
{
	messages.insert(&m);
	m.addfolder(this);
}
void Folder::remove(Message &m)
{
	messages.erase(&m);
	m.remfolder(this);
}
Folder & Folder::operator=(const Folder &rhs)
{
	remove_from_Messages();
	messages=rhs.messages;
	add_to_Messages(rhs);
	return *this;
}
Folder::~Folder()
{
	remove_from_Messages();
}
```
### 13.35
如果使用合成的拷贝构造函数，那么新的Message对象不会被正确的放到对应的Folder中。如果使用合成的拷贝赋值运算符，那么左侧运算对象无法正确从Folder中删除，赋值后也无法放入对应的Folder中。合成的析构函数同样无法正确从Folder中删除。
### 13.36
[见13.34](#1)
### 13.37
[见13.34](#1)
### 13.38
使用拷贝并交换的方式来设计Message的赋值运算符的话，会调用其拷贝构造函数及swap进行交换，这样会多次发生从所有目录中删除和添加到所有目录中的操作，效率低下。
### 13.39
<a id="2">StrVec.h</a>
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
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
		StrVec(const StrVec &);
		StrVec(std::initializer_list<std::string>);
		StrVec & operator=(const StrVec &);
		~StrVec() {free();}
		void push_back(const std::string &);
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
==StrVec.cpp==
```
#include "StrVec.h"
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
```
### 13.40
[见13.39](#2)
### 13.41
使用后置递增运算符，那么相当于现在指针所指位置构造对象，再使指针前进。如果使用前置递增运算的话，first_free当前所指的位置就无法构造到对象。
### 13.42
==13-42.cpp==
```
#include <iostream>
#include <fstream>
#include "TextQuery.h"
#include "QueryResult.h"
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
#include "QueryResult.h"
#include "StrVec.h"
class TextQuery
{
public:
	using line_no=std::vector<std::string>::size_type;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;
private:
	std::shared_ptr<StrVec> file;
	std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
};
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
TextQuery::TextQuery(ifstream &infile):file(new StrVec)
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
	map<string,shared_ptr<set<line_no>>>::const_iterator map_it=wm.find(sought);
	if(map_it==wm.end())
		return QueryResult(sought,nodata,file);
	else
		return QueryResult(sought,map_it->second,file);
}
```
==QueryResult.h==
```
#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include "StrVec.h"
class QueryResult
{
friend std::ostream &print(std::ostream &,const QueryResult &);
public:
	QueryResult(std::string s,std::shared_ptr<std::set<std::vector<std::string>::size_type>> l,std::shared_ptr<StrVec> f):sought(s),lines(l),file(f){}
private:
	std::string sought;
	std::shared_ptr<std::set<std::vector<std::string>::size_type>> lines;
	std::shared_ptr<StrVec> file;
};
std::ostream &print(std::ostream &,const QueryResult &);
inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
{
	return (count>1)?word+ending:word;
}
#endif
```
==QueryResult.cpp==
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
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
		StrVec(const StrVec &);
		StrVec(std::initializer_list<std::string>);
		StrVec & operator=(const StrVec &);
		~StrVec() {free();}
		void push_back(const std::string &);
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
==StrVec.cpp==
```
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
```
### 13.43
我更倾向于指针的表达方式，目的更清晰。
```
void StrVec::free()
{
	if(elements)
	{
		for_each(elements,first_free,[](string &str) {alloc.destroy(&str);});
		alloc.deallocate(elements,cap-elements);
	}
}
```
### 13.44
