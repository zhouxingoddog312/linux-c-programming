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
