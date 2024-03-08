[toc]

### 7.1
```
#include <iostream>
#include <string>
using namespace std;
struct Sales_data
{
	string bookNo;
	unsigned units_sold{0};
	double revenue{0.0};
};
int main(void)
{
	struct Sales_data  total,trans;
	double price;
	if(cin>>total.bookNo)
	{
		cin>>total.units_sold>>price;
		total.revenue=total.units_sold*price;
		while(cin>>trans.bookNo)
		{
			cin>>trans.units_sold>>price;
			trans.revenue=trans.units_sold*price;
			if(total.bookNo==trans.bookNo)
			{
				total.units_sold+=trans.units_sold;
				total.revenue+=trans.revenue;
			}
			else
			{
				cout<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
				total.bookNo=trans.bookNo;
				total.units_sold=trans.units_sold;
				total.revenue=trans.revenue;
			}
		}
		cout<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
	}
	else
	{
		cerr<<"No data?"<<endl;
		return -1;
	}
	return 0;
}
```
### 7.2
```
#include <string>
struct Sales_data
{
	std::string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
};
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
```
### 7.3
```
Sales_data total;
if(read(cin,total))
{
	Sales_data trans;
	while(read(cin,trans))
	{
		if(total.isbn()==trans.isbn())
			total.combine(trans);
		else
		{
			print(cout,total)<<endl;
			total=trans;
		}
	}
	print(cout,total)<<endl;
}
else
	cerr<<"No data?!"<<endl;
```
### 7.4
```
#include <string>
struct Person
{
	std::string name;
	std::string address;
};
```
### 7.5
```
#include <string>
struct Person
{
	std::string name;
	std::string address;
	std::string getName() const { return name; }
	std::string getAddress const { return address; }
};
```
### 7.6
```
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream *os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
```
### 7.7
```
#include <iostream>
#include <string>
using namespace std;
struct Sales_data
{
	std::string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	double avg_price() const;
};
double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream &os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
int main(void)
{
	Sales_data total;
	if(read(cin,total))
	{
		Sales_data trans;
		while(read(cin,trans))
		{
			if(total.isbn()==trans.isbn())
				total.combine(trans);
			else
			{
				print(cout,total)<<endl;
				total=trans;
			}
		}
		print(cout,total)<<endl;
	}
	else
		cerr<<"No data?!"<<endl;
	return 0;
}
```
### 7.8
&emsp;&emsp;因为`read`函数会修改其数值而`print`函数不会。
### 7.9
```
#include <iostream>
#include <string>
struct Person
{
	std::string name;
	std::string address;
	std::string getName() const { return name; }
	std::string getAddress const { return address; }
};
istream & read(istream &is,Person &rp)
{
	is>>rp.name>>rp.address;
	return is;
}
ostream & print(ostream &os,Person &rp)
{
	os<<rp.getName()<<" "<<rp.getAddress();
	return os;
}
```
### 7.10
&emsp;&emsp;从`cin`中读如数据到`data1`，如果成功就再从`cin`中读取数据到`data2`，如果成功就执行`if`后的语句。
### 7.11
```
#include <iostream>
#include <string>
using namespace std;
struct Sales_data
{
	string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	double avg_price() const;
	Sales_data()=default;
	Sales_data(istream &is);
	Sales_data(const string &s):bookNo(s){}
	Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold{n},revenue{n*p}{}
};
double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream &os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
Sales_data::Sales_data(istream &is)
{
	read(is,*this);
}
int main(void)
{
	Sales_data a;
	print(cout,a)<<endl;
	Sales_data b("1992");
	print(cout,b)<<endl;
	Sales_data c{"1992",1,20};
	print(cout,c)<<endl;
	Sales_data d{cin};
	print(cout,d)<<endl;
	return 0;
}
```
### 7.12
```
#include <iostream>
#include <string>
using namespace std;
struct Sales_data;
istream &read(istream &is,Sales_data &item);
struct Sales_data
{
	string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	double avg_price() const;
	Sales_data()=default;
	Sales_data(istream &is){read(is,*this);}
	Sales_data(const string &s):bookNo(s){}
	Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold{n},revenue{n*p}{}
};
double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream &os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
int main(void)
{
	Sales_data a;
	print(cout,a)<<endl;
	Sales_data b("1992");
	print(cout,b)<<endl;
	Sales_data c{"1992",1,20};
	print(cout,c)<<endl;
	Sales_data d{cin};
	print(cout,d)<<endl;
	return 0;
}
```
### 7.13
```
#include <iostream>
#include <string>
using namespace std;
struct Sales_data;
istream &read(istream &is,Sales_data &item);
struct Sales_data
{
	string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	double avg_price() const;
	Sales_data()=default;
	Sales_data(istream &is){read(is,*this);}
	Sales_data(const string &s):bookNo(s){}
	Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold{n},revenue{n*p}{}
};
double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream &os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
int main(void)
{
	Sales_data total{cin};
	Sales_data trans;
	while(read(cin,trans))
	{
		if(total.isbn()==trans.isbn())
			total.combine(trans);
		else
		{
			print(cout,total)<<endl;
			total=trans;
		}
	}
	print(cout,total)<<endl;
	return 0;
}
```
### 7.14
```
Sales_data(const string &s):bookNo(s),units_sold{0},revenue{0.0}{}
```
### 7.15
```
#include <iostream>
#include <string>
struct Person
{
	std::string name;
	std::string address;
	std::string getName() const { return name; }
	std::string getAddress const { return address; }
	Person()=default;
	Person(const std::string &s):name(s){}
	Person(const std::string &s1,const std::string &s2):name{s1},address{s2}{}
	Person(std::istream &is);
};
istream & read(istream &is,Person &rp)
{
	is>>rp.name>>rp.address;
	return is;
}
ostream & print(ostream &os,Person &rp)
{
	os<<rp.getName()<<" "<<rp.getAddress();
	return os;
}
Person::Person(std::istream &is)
{
	read(is,*this);
}
```
### 7.16
&emsp;&emsp;**没有**限制，需要在整个程序内可被访问的接口部分定义在`public`后，实现细节定义在`private`后。
### 7.17
&emsp;&emsp;`class`和`struct`的区别**仅仅**在于**默认访问权限**，`class`的默认访问权限是`private`的，而`struct`的默认访问权限是`public`的。
### 7.18
&emsp;&emsp;封装实现了类的*接口和实现分离*。
### 7.19
&emsp;&emsp;**数据成员**声明成`private`的，**构造函数与接口函数**声明成`public`的。
### 7.20
&emsp;&emsp;**友元**的用处在于**非类的成员**的其它类或函数要访问类的**非公有成员**时。
### 7.21
```
#include <iostream>
#include <string>
using namespace std;
class Sales_data;
istream &read(istream &is,Sales_data &item);
class Sales_data
{
friend Sales_data add(const Sales_data &lhs,const Sales_data &rhs);
friend ostream &print(ostream &os,Sales_data &item);
friend istream &read(istream &is,Sales_data &item);
private:
	string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	double avg_price() const;
public:
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	Sales_data()=default;
	Sales_data(istream &is){read(is,*this);}
	Sales_data(const string &s):bookNo(s){}
	Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold{n},revenue{n*p}{}
};
double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream &os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
int main(void)
{
	Sales_data total{cin};
	Sales_data trans;
	while(read(cin,trans))
	{
		if(total.isbn()==trans.isbn())
			total.combine(trans);
		else
		{
			print(cout,total)<<endl;
			total=trans;
		}
	}
	print(cout,total)<<endl;
	return 0;
}
```
### 7.22
```
#include <iostream>
#include <string>
class Person
{
	friend std::istream & read(std::istream &is,Person &rp);
	friend std::ostream & print(std::ostream &os,const Person &rp);
private:
	std::string name;
	std::string address;
public:
	std::string getName() const { return name; }
	std::string getAddress const { return address; }
	Person()=default;
	Person(const std::string &s):name(s){}
	Person(const std::string &s1,const std::string &s2):name{s1},address{s2}{}
	Person(std::istream &is);
};
std::istream & read(std::istream &is,Person &rp)
{
	is>>rp.name>>rp.address;
	return is;
}
std::ostream & print(std::ostream &os,const Person &rp)
{
	os<<rp.getName()<<" "<<rp.getAddress();
	return os;
}
Person::Person(std::istream &is)
{
	read(is,*this);
}
```
### 7.23
```
#include <string>
class Screen
{
	pubilic:
		using pos=std::string::size_type pos;
		Screen()=default;
		Screen(pos ht,pos wd,char c):height{ht},width{wd},contents(ht*wd,c){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const;
		Screen &move(pos r,pos c);
	private:
		pos cursor=0,height=0,width=0;
		std::string contents;
};
inline char Screen::get(pos r,pos c) const
{
	pos row=r*width;
	return contents[row+c];
}
inline Screen &move(pos r,pos c)
{
	pos row=r*width;
	cursor=row+c;
	return *this;
}
```
### 7.24
```
#include <string>
class Screen
{
	pubilic:
		using pos=std::string::size_type pos;
		Screen()=default;
		Screen(pos ht,pos wd):height{ht},width{wd},contents(ht*wd,' '){}
		Screen(pos ht,pos wd,char c):height{ht},width{wd},contents(ht*wd,c){}
		char get() const {return contents[cursor];}
		char get(pos r,pos c) const;
		Screen &move(pos r,pos c);
	private:
		pos cursor=0,height=0,width=0;
		std::string contents;
};
inline char Screen::get(pos r,pos c) const
{
	pos row=r*width;
	return contents[row+c];
}
inline Screen &move(pos r,pos c)
{
	pos row=r*width;
	cursor=row+c;
	return *this;
}
```
### 7.25
&emsp;&emsp;能，因为`Screen`的数据成员只有**内置类型**和**string类型**，而string类型有自己的拷贝和赋值操作，所以可以依赖于拷贝和赋值操作的默认合成版本。
### 7.26
```
#include <iostream>
#include <string>
using namespace std;
class Sales_data;
istream &read(istream &is,Sales_data &item);
class Sales_data
{
friend Sales_data add(const Sales_data &lhs,const Sales_data &rhs);
friend ostream &print(ostream &os,Sales_data &item);
friend istream &read(istream &is,Sales_data &item);
private:
	string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	double avg_price() const;
public:
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	Sales_data()=default;
	Sales_data(istream &is){read(is,*this);}
	Sales_data(const string &s):bookNo(s){}
	Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold{n},revenue{n*p}{}
};
inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream &os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
int main(void)
{
	Sales_data total{cin};
	Sales_data trans;
	while(read(cin,trans))
	{
		if(total.isbn()==trans.isbn())
			total.combine(trans);
		else
		{
			print(cout,total)<<endl;
			total=trans;
		}
	}
	print(cout,total)<<endl;
	return 0;
}
```
### 7.27
==page246.h==
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
```
#include <iostream>
#include "page246.h"
using namespace std;
int main()
{
	Screen myScreen(5,5,'X');
	myScreen.move(4,0).set('#').display(cout);
	cout<<"\n";
	myScreen.display(cout);
	cout<<'\n';
	return 0;
}
```
### 7.28
&emsp;&emsp;这样的话，只有`move(4,0)`会对`Screen`生效，另外的函数将操作一个临时的副本。
### 7.29
```
待完善
```
### 7.30
&emsp;&emsp;可以明确的表示访问的对象的成员，并且可以在成员函数中使用与数据成员同名的形参，缺点是太繁琐。
### 7.31
```
class Y;
class X
{
	Y *py;
};
class Y
{
	X obj;
};
```
### 7.32
```
#include <string>
class Window_mgr
{
	public:
		using ScreenIndex=std::vector<Screen>::size_type;
		void clear(ScreenIndex i);
		ScreenIndex addScreen(const Screen &);
	private:
		std::vector<Screen> screens{Screen(24,80,' ')};
}
inline Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
	screens.push_back(s);
	return screens.size()-1;
}
class Screen
{
	friend void Window_mgr::clear(ScreenIndex i);
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
inline void Window_mgr::clear(ScreenIndex i)
{
	Screen &s=screens[i];
	s.contents=string(s.height*s.width,' ');
}
```
### 7.33
&emsp;&emsp;`pos`类型定义在类的内部，需要使用作用域说明符。
```
Screen::pos Screen::size() const
{
    return height*width;
}
```
### 7.34
&emsp;&emsp;对`pos`的使用将出现在它的声明之前，编译错误。
### 7.35
```
typedef string Type;
Type initVal();
class Exercise{
    public:
        typedef double Type;
        Type setVal(Type);//此时的Type都是double
        Type initVal();//此时的Type都是double
    private:
        int val;
};
Exercise::Type Exercise::setVal(Type parm){//此行的第一个Type应该指明所属的类
    val=parm+initVal();
    return val;
}
```
### 7.36
&emsp;&emsp;成员的**初始化顺序**与他们**在类定义中的出现顺序**一致，所以这里会先初始化`rem`，但是在构造函数的初始值列表中，用来初始化`rem`的数值存在`base`，而此时`base`还未初始化。
```
struct X {
    X (int i,int j):base(i),rem(i%j) {}
    int rem,base;
};
```
### 7.37
```
Sales_data first_item(cin);//Sales_data(std::istream &is);数据成员的值依赖于输入
int main(){
    Sales_data next;//Sales_data(std::string s="");bookNo默认初始化为空字符串，其余数据成员使用类内初始值值初始化为0.
    Sales_data last("9-999-99999-9");//Sales_data(const std::string &);bookNo初始化为9-999-99999-9，其余数据成员使用类内初始值初始化为0.
}
```
### 7.38
`Sales_data(std::istream &is=std::cin);`
### 7.39
&emsp;&emsp;不合法，两个函数都具有了**默认构造函数**的作用，会产生二义性错误。
### 7.40
```
class Employee
{
public:
	Employee()=default;
	Employee(std::string s):name(s){}
	Employee(std::string s,unsigned int i,double j,unsigned int k):name(s),Age(i),salary(j),Phone_Number(k){}
private:
	std::string name;
	unsigned int Age=0;
	double salary=0;
	unsigned int Phone_Number=0;
}
```
### 7.41
```
#include <iostream>
#include <string>
using namespace std;
class Sales_data;
istream &read(istream &is,Sales_data &item);
class Sales_data
{
friend Sales_data add(const Sales_data &lhs,const Sales_data &rhs);
friend ostream &print(ostream &os,Sales_data &item);
friend istream &read(istream &is,Sales_data &item);
private:
	string bookNo;
	unsigned units_sold=0;
	double revenue=0.0;
	double avg_price() const;
public:
	std::string isbn() const  {return bookNo;}
	Sales_data &combine(const Sales_data &);
	Sales_data():Sales_data("",0,0){std::cout<<"This is the default constructor."<<endl;}
	Sales_data(istream &is):Sales_data(){read(is,*this);cout<<"This is the iostream constructor."<<endl;}
	Sales_data(const string &s):Sales_data(s,0,0){cout<<"This is the single string constructor."<<endl;}
	Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold{n},revenue{n*p}{cout<<"This is the three parameter constructor."<<endl;}
};
inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue/units_sold;
	else
		return 0;
}
Sales_data & Sales_data::combine(const Sales_data &rhs)
{
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}
istream &read(istream &is,Sales_data &item)
{
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	return is;
}
ostream &print(ostream &os,Sales_data &item)
{
	os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
	return os;
}
Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
	Sales_data sum=lhs;
	sum.combine(rhs);
	return sum;
}
int main(void)
{
	Sales_data a;
	Sales_data b{"hi"};
	Sales_data c{"hi",1,1};
	Sales_data d{cin};
	return 0;
}
```
### 7.42
```
class Employee
{
public:
	Employee():Employee("",0,0,0){}
	Employee(std::string s):Employee(s,0,0,0){}
	Employee(std::string s,unsigned int i,double j,unsigned int k):name(s),Age(i),salary(j),Phone_Number(k){}
private:
	std::string name;
	unsigned int Age=0;
	double salary=0;
	unsigned int Phone_Number=0;
}
```
### 7.43
```
class NoDefault
{
public:
	val v;
	NoDefault(int i):val(i){}
};
class C
{
public:
	NoDefault no;
	C(int i=0):no(i){}
};
```
### 7.44
&emsp;&emsp;不合法，`NoDefault`类没有**默认构造函数**，无法默认初始化`vector`的元素。
### 7.45
&emsp;&emsp;合法，`C`有**默认构造函数**。
### 7.46
1. 错误，可以依赖**合成的默认构造函数**
2. 错误，可以带有**默认实参**
3. 错误，因为如果一个类没有**默认构造函数**，也就是说我们定义了该类的某些构造函数但是没有为其设计默认构造函数，则当编译器确实需要隐式地使用默认构造函数时，该类无法使用。所以一般情况下，都应该为类构建一个默认构造函数
4. 错误，类类型成员执行各自的**默认构造函数**，内置类型和复合类型的成员只对定义在**全局作用域中**的对象执行初始化
### 7.47
&emsp;&emsp;设为`explicit`可以避免误将`string`对象转换为`Sales_data`。
### 7.48
```
string null_isbn("9-999-99999-9");
Sales_data item1(null_isbn);//由null_isbn转换一个Sales_data临时量用于初始化item1
Sales_data item2("9-999-99999-9");//错误，只允许一步类类型转换，这种情况必须显示调用构造函数
```
### 7.49
1. 值传递，`string`生成`Sales_data`临时量
2. 错误，临时量无法赋予非常量引用
3. 可以调用，但此函数是常量成员函数，无法改变调用的对象，所以无法达到调用目的
### 7.50
```
#include <iostream>
#include <string>
class Person
{
	friend std::istream & read(std::istream &is,Person &rp);
	friend std::ostream & print(std::ostream &os,const Person &rp);
private:
	std::string name;
	std::string address;
public:
	std::string getName() const { return name; }
	std::string getAddress const { return address; }
	Person()=default;
	explicit Person(const std::string &s):name(s){}
	Person(const std::string &s1,const std::string &s2):name{s1},address{s2}{}
	explicit Person(std::istream &is);
};
std::istream & read(std::istream &is,Person &rp)
{
	is>>rp.name>>rp.address;
	return is;
}
std::ostream & print(std::ostream &os,const Person &rp)
{
	os<<rp.getName()<<" "<<rp.getAddress();
	return os;
}
Person::Person(std::istream &is)
{
	read(is,*this);
}
```
### 7.51
&emsp;&emsp;例如将一个`int`值转换成`vector`，意义不明确。
### 7.52
&emsp;&emsp;这里程序的意图是提供一个花括号括起来的成员初始值列表对`item`进行初始化，但是这要求`item`是聚合类，所以应该去掉`Sales_data`类的**类内初始值**。
### 7.53
```
class Debug
{
public:
	constexpr Debug(bool b=true):hw(b),io(b),other(b){}
	constexpr Debug(bool h,bool i,bool o):hw(h),io(i),other(o){}
	constexpr bool any(){return hw||io||other;}
	void set_hw(bool b){hw=b;}
	void set_io(bool b){io=b;}
	void set_other(bool b){other=b;}
private:
	bool hw;
	bool io;
	bool other;
};
```
### 7.54
&emsp;&emsp;不能，这些函数用于设置数据成员的值，而`constexpr`函数成员是隐式`const`的。
### 7.55
不是，它虽然是**聚合类**，但它的**数据成员s**不是**字面值类型**。
### 7.56
&emsp;&emsp;静态成员是指声明语句之前带有关键字`static`的类成员，静态成员不是任意单独对象的组成部分，而是由该类的全体对象所共享。
静态成员的**优点**包括：作用域位于类的范围之内，避免与其他类的成员或者全局作用域的名字冲突；可以是私有成员；通过阅读程序可以非常容易地看出静态成员与特定类关联，使得程序的含义清晰明了。
静态成员与普通成员的**区别**主要体现在：普通成员与类的对象关联，是某个具体对象的组成部分；而静态成员不从属于任何具体的对象，它由该类的所有对象共享。另外，还有一个细微的区别，静态成员可以作为默认实参，而普通数据成员不能作为默认实参。
### 7.57
```
class Account
{
public:
	void calculate(){amount+=amount*interestRate;}
	static double rate(){return interestRate;}
	static void rate(double);
private:
	std::string owner;
	double amount;
	static double interestRate;
	static double initRate();
};
void Account::rate(double newRate)
{
	interestRate=newRate;
}
double Account::initRate()
{
	return 0.0;
}
double Account::interestRate=initRate();
```
### 7.58
```
class Example
{
public:
	static double rate;
	static constexpr int vecSize=20;
	static vector<double> vec;
};
double Example::rate=6.5;
constexpr int Example::vecSize;
vector<double> Example::vec(vecSize);
```
