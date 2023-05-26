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
