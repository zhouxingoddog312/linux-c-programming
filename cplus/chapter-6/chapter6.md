[toc]

### 6.1
&emsp;&emsp;实参是形参的初始值，形参用于函数的声明与定义，实参用于函数调用时用来初始化形参。
### 6.2
1.
&emsp;&emsp;原文函数体中的返回值与定义的返回类型不符
```
string f()
{
    string s;
    //...
    return s;
}
```
2.
&emsp;&emsp;缺少返回类型
```
void f2(int i) {/*......*/}
```
3.
&emsp;&emsp;函数体应该用一对花括号包裹，形参名不能重复
```
int calc(int v1,int v2){/*......*/}
```
4.
&emsp;&emsp;函数体应该用一对花括号包裹
```
double square(double x) {return x*x;}
```
### 6.3
```
#include <iostream>
using namespace std;
int fact(int val)
{
	int ret=1;
	for(int i=1;i<=val;++i)
		ret*=i;
	return ret;
}
int main()
{
	int j=fact(5);
	cout<<"5! is "<<j<<endl;
	return 0;
}
```
### 6.4
```
#include <iostream>
using namespace std;
int fact_1(void)
{
	int val;
	cout<<"Enter a number:";
	cin>>val;
	int ret=1;
	for(int i=1;i<=val;++i)
		ret*=i;
	return ret;
}
int main()
{
	int j=fact_1();
	cout<<"The factorial is "<<j<<endl;
	return 0;
}
```
### 6.5
```
#include <iostream>
using namespace std;
unsigned absolute(int val)
{
	return val>=0?val:-val;
}
int main(void)
{
	int val;
	cout<<"Enter a integer:";
	cin>>val;
	cout<<"The absolute value of "<<val<<" is "<<absolute(val)<<endl;
	return 0;
}
```
### 6.6
&emsp;&emsp;形参和函数体内部定义的变量统称为局部变量，局部变量在超出它所在的作用域时被销毁。而局部静态变量第一次经过它的定义语句时初始化，直到程序终止才被销毁。
```
#include <iostream>
using namespace std;
size_t count_calls(int )
{
	int localval=0;
	static size_t ctr=0;
	cout<<"The localval is "<<localval<<" ,but the static value is "<<ctr<<endl;
	return ++ctr;
}
int main(void)
{
	for(int i=0;i!=10;++i)
		count_calls(1);
	return 0;
}
```
### 6.7
```
#include <iostream>
using namespace std;
size_t count_calls()
{
	static size_t ctr=0;
	return ctr++;
}
int main(void)
{
	for(int i=0;i!=10;++i)
		cout<<count_calls()<<endl;
	return 0;
}
```
### 6.8
==Chapter6.h==
```
int fact(int);
int fact_1(void);
unsigned absolute(int);
```
### 6.9
==fact.cc==
```
#include "Chapter6.h"
int fact(int val)
{
	int ret=1;
	for(int i=1;i<=val;++i)
		ret*=i;
	return ret;
}
```
==factMain.cc==
```
#include <iostream>
#include "Chapter6.h"
using namespace std;
int main()
{
	int j=fact(5);
	cout<<"5! is "<<j<<endl;
	return 0;
}
```
### 6.10
```
#include <iostream>
using namespace std;
void Swap(int *p,int *q)
{
	int temp;
	temp=*p;
	*p=*q;
	*q=temp;
}
int main(void)
{
	int p=3,q=5;
	Swap(&p,&q);
	cout<<"Now,p="<<p<<" q="<<q<<endl;
	return 0;
}
```
### 6.11
```
#include <iostream>
using namespace std;
void reset(int &i)
{
	i=0;
}
int main()
{
	int i=99;
	reset(i);
	cout<<"i="<<i<<endl;
	return 0;
}
```
### 6.12
```
#include <iostream>
using namespace std;
void Swap(int &p,int &q)
{
	int temp;
	temp=p;
	p=q;
	q=temp;
}
int main(void)
{
	int p=3,q=5;
	Swap(p,q);
	cout<<"Now,p="<<p<<" q="<<q<<endl;
	return 0;
}
```
### 6.13
&emsp;&emsp;一个是传值调用，形参是实参的拷贝，一个是传引用调用，形参是实参的别名。
### 6.14
&emsp;&emsp;当函数的目的是交换两个参数的内容时应该使用引用类型的形参。
&emsp;&emsp;当参数是string对象时，为了避免拷贝很长的字符串，应该使用引用类型。
&emsp;&emsp;在其他情况下可以使用值传递的方式，而无须使用引用传递，例如求整数的绝对值或者阶乘的程序。
### 6.15
&emsp;&emsp;因为不需要改变`s`的值，而需要改变`occurs`的值，所以`s`是**常量引用**而`occurs`是**普通引用**。因为`c`的类型是**内置类型**，拷贝消耗低，所以不需要用引用类型。如果令s是普通引用，有可能破坏原始数据，而令occurs是常量引用的话，无法达到记录次数的目的。
### 6.16
&emsp;&emsp;它只能接受`string`类型的实参，而无法接受`const string`类型的实参，改为如下：
`bool is_empty(const string &s) {return s.empty();}`
### 6.17
```
#include <iostream>
using namespace std;
bool has_upper(const string &s)
{
	for(auto c:s)
	{
		if(isupper(c))
			return true;
	}
	return false;
}
void to_lower(string &s)
{
	for(auto &c:s)
	{
		if(isupper(c))
			c=tolower(c);
	}
}
int main()
{
	string s;
	cin>>s;
	if(has_upper(s))
	{
		cout<<"has upper"<<endl;
		to_lower(s);
		cout<<"the lower case is "<<s<<endl;
	}
	else
		cout<<"pure lower"<<endl;
	return 0;
}
```
### 6.18
1. `bool compare(const matrix &m1,const matrix &m2);`
2. `vector<int>::iterator change_val(int val,vector<int>::iterator it);`
### 6.19
1. 实参数量与形参不符
2. 合法
3. 合法
4. 合法
### 6.20
&emsp;&emsp;不需要改变形参的值时，应该是常量引用。可能会破坏原始数据，也会限制函数所能接收的实参类型。
### 6.21
```
int compare(const int a,const int *pb)
{
	return a>*pb?a:*pb;
}
```
### 6.22
```
void swap(int * &pa,int * &pb)
{
	int *temp;
	temp=pa;
	pa=pb;
	pb=temp;
}
```
### 6.23
```
#include <iostream>
using namespace std;
void print(const int i)
{
	cout<<i<<endl;
}
void print(const int *beg,const int *end)
{
	while(beg!=end)
		cout<<*beg++<<endl;
}
int main(void)
{
	int i=0,j[2]={0,1};
	print(i);
	print(begin(j),end(j));
	return 0;
}
```
### 6.24
&emsp;&emsp;如果传入的数组大小小于10,就会越界。
```
void print(const int *ia,const size_t sz)
{
    for(size_t i=0;i!=sz;++i)
        cout<<ia[i]<<endl;
}
```
### 6.25
```
#include <iostream>
#include <string>
using namespace std;
int main(int argc,char *argv[])
{
	string s;
	for(size_t index=1;index!=argc;++index)
		s+=argv[index];
	cout<<s<<endl;
	return 0;
}
```
### 6.26
```
#include <iostream>
#include <string>
using namespace std;
int main(int argc,char *argv[])
{
	for(size_t index=1;index!=argc;++index)
		cout<<argv[index]<<endl;
	return 0;
}
```
### 6.27
```
#include <iostream>
using namespace std;
int sum(initializer_list<int> il)
{
	int ret=0;
	for(auto &elem:il)
		ret+=elem;
	return ret;
}
int main()
{
	cout<<sum({1,2,3})<<endl;
	return 0;
}
```
### 6.28
`const string &`
### 6.29
&emsp;&emsp;当`initializer_list`对象的元素类型是**类类型**或**容器类型**时，为避免拷贝，就可以声明成**引用类型**。
### 6.30
```
#include <string>
using std::string;
bool str_substring(const string &str1,const string &str2)
{
	if(str1.size()==str2.size())
		return str1==str2;
	auto size=(str1.size()<str2.size())?str1.size():str2.size();
	for(decltype(size) i=0;i!=size;++i)
		if(str1[i]!=str2[i])
			return;
}
```
### 6.31
&emsp;&emsp;返回函数局部变量的引用无效。
### 6.32
&emsp;&emsp;合法，返回array数组index索引的元素的引用。
### 6.33
```
#include <iostream>
#include <vector>
using namespace std;
void print(vector<int>::iterator beg,vector<int>::iterator end)
{
	if(beg!=end)
	{
		cout<<*beg++<<" ";
		print(beg,end);
	}
	else
		return;
}
int main(void)
{
	vector<int> vi={1,2,3,7,4,5,6};
	print(vi.begin(),vi.end());
	return 0;
}
```
### 6.34
&emsp;&emsp;当传入实参是**负数**时，递归无法停止。
### 6.35
&emsp;&emsp;`val--`的值是原值的副本，同时会导致`val`的**递减操作**与**读取val的值的操作**出现在同一个表达式中。
### 6.36
```
string (&fun(void)) [10];
```
### 6.37
```
typedef string arrT[10];
arrT &func(void);


auto func(void)->string (&) [10];


string arrS[10];
decltype(arrS) &func(void);
```
### 6.38
```
int odd[]={1,3,5,7,9};
int even[]={0,2,4,6,8};
decltype(odd) &arrPtr(int i)
{
	return (i%2)?odd:even;
}
```
### 6.39
1. 非法，顶层const形参与非顶层const形参无法区分。
2. 非法，除了返回类型外，其余要素都相同。
3. double指针的形参，返回double指针。
### 6.40
1. 正确
2. 错误，一旦某个形参被赋予默认实参，后面所有的形参都必须有默认实参。
### 6.41
1. 非法，形参ht并无默认实参。
2. 合法。
3. 合法，但是'*'将被隐式转换为int赋予wd。
### 6.42
```
#include <iostream>
#include <string>
using namespace std;
string make_plural(size_t ctr,const string &word,const string &ending="s")
{
	return (ctr>1)?word+ending:word;
}
int main(void)
{
	cout<<make_plural(1,"success","es")<<endl;
	cout<<make_plural(2,"success","es")<<endl;
	cout<<make_plural(1,"failure")<<endl;
	cout<<make_plural(2,"failure")<<endl;
	return 0;
}
```
### 6.43
1. 声明与定义都放在头文件中。
2. 声明放在头文件中，定义放在源文件中。
### 6.44
```
inline bool isShorter(const string &s1,const string &s2)
{
	return s1.size()<s2.size();
}
```
### 6.45
内联函数适用于规模较小、流程直接、频繁调用的函数。
### 6.46
不能，返回类型不是常量表达式。
### 6.47
```
#include <iostream>
#include <vector>
using namespace std;
void print(vector<int>::iterator beg,vector<int>::iterator ends)
{
#ifndef NDEBUG
	cout<<"Now, in the function "<<__func__<<" At the line "<<__LINE__<<". The size of the vector is"<<ends-beg<<endl;
#endif
	if(beg!=ends)
	{
		cout<<*beg++<<" ";
		print(beg,ends);
	}
	else
		return;
}
int main(void)
{
	vector<int> vi={1,2,3,7,4,5,6};
	print(vi.begin(),vi.end());
	return 0;
}
```
### 6.48
&emsp;&emsp;此循环，读取标准输入，结果和`sought`比较，不同则继续读取，相同则判断。
assert的使用不合理，程序执行到`assert`的原因可能有两个，一是用户终止了输入，二是用户输入的内容正好与`sought`的内容一样。如果用户尝试终止输入，则`assert`的条件为假，输出错误信息，这与程序的原意是不相符的。
### 6.49
**候选函数**就是与被调用函数同名，声明在调用点可见的函数。
**可行函数**就是形参与实参数量相等，且类型相同或可转换的函数。
### 6.50
1. 二义性
2. `void f(int);`
3. `void f(int,int);`
4. `void f(double,double);`
### 6.51
```
#include <iostream>
using namespace std;
void f();
void f(int);
void f(int ,int);
void f(double,double);
int main(void)
{
	f(42);
	f(42,0);
	f(2.56,3.14);
	return 0;
}
void f()
{
	cout<<"This is function f()."<<endl;
}
void f(int)
{
	cout<<"This is function f(int)."<<endl;
}
void f(int ,int)
{
	cout<<"This is function f(int,int)."<<endl;
}
void f(double,double=3.14)
{
	cout<<"This is function f(double,double=3.14)."<<endl;
}
```
### 6.52
1. 类型提升
2. 算术类型转换
### 6.53
1. 合法，底层const
2. 合法，底层const
3. 不合法，顶层const
### 6.54
```
int func(int,int);
vector<int (*)(int,int)> vc;
```
### 6.55
```
#include <iostream>
#include <vector>
using namespace std;
int func_sum(int i,int j)
{
	return i+j;
}
int func_reduce(int i,int j)
{
	int temp=i-j;
	return (temp>=0)?temp:-temp;
}
int func_multiplicate(int i,int j)
{
	return i*j;
}
int func_division(int i,int j)
{
	return i/j;
}
int main()
{
	typedef int Func(int,int);
	vector<Func *> vF;
	vF.push_back(func_sum);
	vF.push_back(func_reduce);
	vF.push_back(func_multiplicate);
	vF.push_back(func_division);
	return 0;
}
```
### 6.56
```
#include <iostream>
#include <vector>
using namespace std;
int func_sum(int i,int j)
{
	return i+j;
}
int func_reduce(int i,int j)
{
	int temp=i-j;
	return (temp>=0)?temp:-temp;
}
int func_multiplicate(int i,int j)
{
	return i*j;
}
int func_division(int i,int j)
{
	return i/j;
}
int main()
{
	typedef int Func(int,int);
	vector<Func *> vF;
	vF.push_back(func_sum);
	vF.push_back(func_reduce);
	vF.push_back(func_multiplicate);
	vF.push_back(func_division);
	int i=2,j=3;
	cout<<"sum= "<<vF[0](i,j)<<endl;
	cout<<"reduce= "<<vF[1](i,j)<<endl;
	cout<<"multiplicate= "<<vF[2](i,j)<<endl;
	cout<<"division= "<<vF[3](i,j)<<endl;
	return 0;
}
```
