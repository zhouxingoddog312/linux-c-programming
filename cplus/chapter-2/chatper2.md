[toc]
### 2.1
int、long、long long和short表示整型类型，C语言规定它们表示数的范围short<int<long<long long。其中，数据类型long long是在C11中新定义的；
除去布尔型和扩展的字符型之外，其它整型可以划分为**带符号的（signed）和无符号的（unsigned）**两种。带符号类型可以表示正数、负数和0，无符号类型则仅能表示大于等于0的值。类型int、short、long和long long都是带符号的，通过在这些类型名前添加unsigned就可以得到无符号类型，例如unsigned long。类型unsigned int可以缩写为unsigned；
float和double用于表示浮点数，其中，float表示单精度浮点数，double表示双精度浮点数。执行浮点数运算选用double，这是因为float通常精度不够而且双精度浮点数和单精度浮点数的计算代价相差无几。事实上，对于某些机器来说，双精度运算甚至比单精度还快。long double提供的精度在一般情况下是没有必要的，况且它带来的运算时消耗也不容忽视。
### 2.2
利率（rat）：float，本金（principal）：long long，付款（payment）：long long。
利率一般是小数点后保留四位有效数字，float 合适；
因为float和double都是浮点数, 都有取值范围, 都有精度范围.浮点数与通常使用的小数不同,使用中,往往难以确定。所以说，float和double都是不能用来表示精确的类型的.金额必须是完全精确的计算, 故不能使用double或者float.本金和付款使用最大的带符号整型表示.
### 2.3
32
4294967264
32
-32
0
0
### 2.4
```
#include <iostream>
int main()
{
	unsigned u=10,u2=42;
	std::cout<<u2-u<<std::endl;
	std::cout<<u-u2<<std::endl;
	int i=10,i2=42;
	std::cout<<i2-i<<std::endl;
	std::cout<<i-i2<<std::endl;
	std::cout<<i-u<<std::endl;
	std::cout<<u-i<<std::endl;
	return 0;
}
```
### 2.5
1.
|字面值|数据类型|
|-|-|
|'a'|char|
|L'a'|wchar_t|
|"a"|const char *|
|L"a"|const wchar_t *|
2.
|字面值|数据类型|
|-|-|
|10|int|
|10u|unsigned|
|10L|long|
|10uL|unsigned long|
|012|int八进制9|
|0xC|int十六进制12|
3.
|字面值|数据类型|
|-|-|
|3.14|double|
|3.14f|float|
|3.14L|long double|
4.
|字面值|数据类型|
|-|-|
|10|int|
|10u|unsigned|
|10.|double|
|10e-2|double|
### 2.6
有区别，第二个表达式数值以0开头表示八进制，但是09不合法
### 2.7
|字面值|数据类型|
|-|-|
|"Who goer withF\145rgus?\012"|const char *其中还有两个八进制转义序列|
|3.14e1L|long double|
|1024f|float|
|3.14L|long double|
### 2.8
```
#include <iostream>
int main()
{
	std::cout<<"\062\115\xA";
	std::cout<<"\x32\x9\x4d\012";
	return 0;
}
```
### 2.9
1. 变量需要先定义后使用`int input_value;std::cin>>intput_value`
2. 初始值存在丢失信息的风险`double i={3.14}`
3. 格式错误`double salary,wage;salary=wage=9999.99`
4. 正确，隐式转换
### 2.10
```
std::string global_str;//空字符串
int global_int;//0
int main()
{
    int local_int;//未定义
    std::string local_str;//空字符串
}
```
### 2.11
1. 定义
2. 声明并定义
3. 声明
### 2.12
1. 非法
2. 合法
3. 非法
4. 非法
5. 合法
### 2.13
100
### 2.14
100 45

### 2.15
1. 合法，会进行隐式转换
2. 非法，引用不能绑定到字面值上
3. 合法
4. 非法，引用必须被初始化
### 2.16
1. 合法，给变量d赋值
2. 合法，会进行隐式转换
3. 合法
4. 合法
### 2.17
10  10
### 2.18
```
#include <iostream>
int main()
{
	int *ptr,a;
	//更改指针的值
	ptr=nullptr;
	ptr=&a;
	//更改指针所指对象的值
	*ptr=3;
	std::cout<<"a="<<a<<std::endl;
	return 0;
}
```
### 2.19
引用（reference）为对象起了另外一个名字，引用类型引用（refers to）另外一种类型。
指针（pointer）是"指向（point to）"另外一种类型的复合类型。与引用类似，指针也实现了对其他对象的间接访问。然而指针与引用相比又有很多不同点。
指针本身就是一个对象，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象；
指针无须在定义时赋初值；
因为引用不是对象，没有实际地址，所以不能定义指向引用的指针；
除特殊情况，其他所有指针的类型都要和它所指向的对象严格匹配；
### 2.20
`int i=42;`定义整型变量i，初始化为42
`int *p1=&i;`定义整型指针p1,初始化为变量i的地址
`*p1=*p1**p1;`指针p1所指对象赋值为其自身值的平方
### 2.21
1. 指针类型与对象不匹配
2. 应该为指针赋值地址而非对象
3. 合法
### 2.22
1. 如果p是非空指针
2. 如果指针p所指对象的值不为0
### 2.23
不能，所以推荐使用智能指针。
### 2.24
void类型指针可以存放任意类型对象的地址，而lp的指针类型与对象不匹配。
### 2.25
1. 整型类型指针ip，整型i，整型类型引用r。
2. 整型i，整型类型指针ip初始化为空指针。
3. 整型类型指针ip，整型类型ip2。
### 2.26
1. const变量必须初始化
2. 合法
3. 合法
4. const变量不能改变其值
### 2.27
1. 引用不能绑定字面值
2. 合法
3. 合法
4. 合法
5. 合法
6. 没有顶层const引用
7. 合法
### 2.28
1. 常量指针必须初始化
2. 同上
3. 常量必须初始化
4. 指向常量的常量指针必须初始化
5. 合法
### 2.29
1. 合法
2. 常量指针不能直接转换为非常量指针
3. 指针类型应该与所指对象一致
4. 指向常量的指针不能用于改变所指对象的值
5. 常量指针不能改变自身所指对象
6. const对象的值不能被改变
### 2.30
1. 顶层
2. 非const常量
3. 非指针常量，非const引用
4. 底层const，顶、底层const，底层const
### 2.31
1. 合法v2是顶层const
2. 非法，p2是底层const，p1不是
3. 非法，p3是底层const而p1不是。合法，p2和p3有相同的底层const资格。
### 2.32
`int null=0, *p=&null;`
### 2.33
2-34.cpp: In function ‘int main()’:
2-34.cpp:20:11: 错误：invalid conversion from ‘int’ to ‘int*’ [-fpermissive]
   20 |         d=42;
      |           ^~
      |           |
      |           int
2-34.cpp:24:11: 错误：invalid conversion from ‘int’ to ‘const int*’ [-fpermissive]
   24 |         e=42;
      |           ^~
      |           |
      |           int
2-34.cpp:28:10: 错误：向只读形参‘g’赋值
   28 |         g=42;
      |         ~^~~
### 2.34
```
#include <iostream>
int main()
{
	int i=0,&r=i;
	const int ci=i,&cr=ci;
	auto a=r;
	std::cout<<"a="<<a<<std::endl;
	a=42;
	std::cout<<"a="<<a<<std::endl;
	auto b=ci;
	std::cout<<"b="<<b<<std::endl;
	b=42;
	std::cout<<"b="<<b<<std::endl;
	auto c=cr;
	std::cout<<"c="<<c<<std::endl;
	c=42;
	std::cout<<"c="<<c<<std::endl;
	auto d=&i;
	std::cout<<"d="<<d<<std::endl;
	d=42;
	std::cout<<"d="<<d<<std::endl;
	auto e=&ci;
	std::cout<<"e="<<e<<std::endl;
	e=42;
	std::cout<<"e="<<e<<std::endl;
	auto &g=ci;
	std::cout<<"g="<<g<<std::endl;
	g=42;
	std::cout<<"g="<<g<<std::endl;
	return 0;
}
```
### 2.35
```
const int i=42;
auto j=i;//int
const auto &k=i;//int
auto *p=&i;//const int
const auto j2=i,&k2=i;//int
```
### 2.36
```
#include <iostream>
int main()
{
	int a=3,b=4;
	decltype(a) c=a;
	decltype((b)) d=a;
	++c;
	++d;
	std::cout<<"a="<<a<<" b="<<b<<" c="<<c<<" d="<<d<<std::endl;
	return 0;
}
```
a   int 4
b   int 4
c   int 4
d   int 4
### 2.37
a   int 3
b   int 4
c   int 3
d   int &   3
### 2.38
auto和decltype的区别主要有三方面：
auto类型说明符用编译器计算变量的初始值来推断其类型，而decltype虽然也让编译器分析表达式并得到它的类型，但是不实际计算表达式的值。
编译器推断出来的auto类型有时候和初始值的类型并不完全一样，编译器会适当地改变结果类型使其更符合初始化规则。例如，auto一般会忽略掉顶层const，而把底层const保留下来。与之相反，decltype会保留变量的顶层const。
与auto不同，decltype的结果类型与表达式密切相关，如果变量名加上了一对括号，则得到的类型与不加括号时会有不同。如果decltype使用的是一个不加括号的变量，则得到的结果就是该变量的类型；如果给变量加上了一层或多层括号，则编译器将推断得到引用类型。
### 2.39
```
#include <iostream>
struct Foo{}
int main()
{
	return 0;
}
```
2-39.cpp:2:13: 错误：结构定义后需要‘;’
    2 | struct Foo{}
      |             ^
      |             ;
### 2.40
```
struct Sales_data
{
	std::string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
```
### 2.41
==2-41-1.cpp==
```
#include <iostream>
#include <string>
struct Sales_data
{
	std::string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data temp;
	double price=0.0;
	while(std::cin>>temp.Bookno)
	{
		std::cin>>temp.sold>>price;
		temp.revenue=temp.sold*price;
		std::cout<<temp.Bookno<<" "<<temp.sold<<" "<<temp.revenue<<std::endl;
		price=0;
	}
	return 0;
}
```
==2-41-2.cpp==
```

#include <iostream>
#include <string>
struct Sales_data
{
	std::string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data temp1,temp2;
	double price=0;
	std::cin>>temp1.Bookno>>temp1.sold>>price;
	temp1.revenue=temp1.sold*price;
	price=0;
	std::cin>>temp2.Bookno>>temp2.sold>>price;
	temp2.revenue=temp2.sold*price;
	if(temp1.Bookno==temp2.Bookno)
		std::cout<<temp1.Bookno<<" "<<temp1.sold+temp2.sold<<" "<<temp1.revenue+temp2.revenue<<std::endl;
	else
		std::cerr<<"not the same isbn";
	return 0;
}
```
==2-41-3.cpp==
```
#include <iostream>
#include <string>
struct Sales_data
{
	std::string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data temp1,temp2;
	double price=0.0;
	if(std::cin>>temp1.Bookno)
	{
		std::cin>>temp1.sold>>price;
		temp1.revenue=temp1.sold*price;
		price=0;
		while(std::cin>>temp2.Bookno)
		{
			std::cin>>temp2.sold>>price;
			temp2.revenue=temp2.sold*price;
			price=0;
			if(temp1.Bookno==temp2.Bookno)
			{
				temp1.sold+=temp2.sold;
				temp1.revenue+=temp2.revenue;
			}
			else
			{
				std::cerr<<"not the same isbn"<<std::endl;
				return -1;
			}
		}
		std::cout<<temp1.Bookno<<" "<<temp1.sold<<" "<<temp1.revenue<<std::endl;
	}
	return 0;
}
```
==2-41-4.cpp==
```
#include <iostream>
#include <string>
struct Sales_data
{
	std::string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data total,temp;
	double price=0.0;
	if(std::cin>>total.Bookno)
	{
		std::cin>>total.sold>>price;
		total.revenue=total.sold*price;
		while(std::cin>>temp.Bookno)
		{
			std::cin>>temp.sold>>price;
			temp.revenue=temp.sold*price;
			price=0;
			if(total.Bookno==temp.Bookno)
			{
				total.sold+=temp.sold;
				total.revenue+=temp.revenue;
			}
			else
			{
				std::cout<<total.Bookno<<" "<<total.sold<<" "<<total.revenue<<std::endl;
				total.Bookno=temp.Bookno;
				total.sold=temp.sold;
				total.revenue=temp.revenue;
			}
		}
		std::cout<<total.Bookno<<" "<<total.sold<<" "<<total.revenue<<std::endl;
	}
	else
	{
		std::cerr<<"no data."<<std::endl;
		return -1;
	}
	return 0;
}
```
### 2.42
==2-42-1.cpp==
```
#include <iostream>
#include <string>
#include "Sales_data.h"
int main()
{
	Sales_data temp;
	double price=0.0;
	while(std::cin>>temp.Bookno)
	{
		std::cin>>temp.sold>>price;
		temp.revenue=temp.sold*price;
		std::cout<<temp.Bookno<<" "<<temp.sold<<" "<<temp.revenue<<std::endl;
		price=0;
	}
	return 0;
}
```
==2-42-2.cpp==
```
#include <iostream>
#include <string>
#include "Sales_data.h"
int main()
{
	Sales_data temp1,temp2;
	double price=0;
	std::cin>>temp1.Bookno>>temp1.sold>>price;
	temp1.revenue=temp1.sold*price;
	price=0;
	std::cin>>temp2.Bookno>>temp2.sold>>price;
	temp2.revenue=temp2.sold*price;
	if(temp1.Bookno==temp2.Bookno)
		std::cout<<temp1.Bookno<<" "<<temp1.sold+temp2.sold<<" "<<temp1.revenue+temp2.revenue<<std::endl;
	else
		std::cerr<<"not the same isbn";
	return 0;
}
```
==2-42-3.cpp==
```
#include <iostream>
#include <string>
#include "Sales_data.h"
int main()
{
	Sales_data temp1,temp2;
	double price=0.0;
	if(std::cin>>temp1.Bookno)
	{
		std::cin>>temp1.sold>>price;
		temp1.revenue=temp1.sold*price;
		price=0;
		while(std::cin>>temp2.Bookno)
		{
			std::cin>>temp2.sold>>price;
			temp2.revenue=temp2.sold*price;
			price=0;
			if(temp1.Bookno==temp2.Bookno)
			{
				temp1.sold+=temp2.sold;
				temp1.revenue+=temp2.revenue;
			}
			else
			{
				std::cerr<<"not the same isbn"<<std::endl;
				return -1;
			}
		}
		std::cout<<temp1.Bookno<<" "<<temp1.sold<<" "<<temp1.revenue<<std::endl;
	}
	return 0;
}
```
==2-42-4.cpp==
```
#include <iostream>
#include <string>
#include "Sales_data.h"
int main()
{
	Sales_data total,temp;
	double price=0.0;
	if(std::cin>>total.Bookno)
	{
		std::cin>>total.sold>>price;
		total.revenue=total.sold*price;
		while(std::cin>>temp.Bookno)
		{
			std::cin>>temp.sold>>price;
			temp.revenue=temp.sold*price;
			price=0;
			if(total.Bookno==temp.Bookno)
			{
				total.sold+=temp.sold;
				total.revenue+=temp.revenue;
			}
			else
			{
				std::cout<<total.Bookno<<" "<<total.sold<<" "<<total.revenue<<std::endl;
				total.Bookno=temp.Bookno;
				total.sold=temp.sold;
				total.revenue=temp.revenue;
			}
		}
		std::cout<<total.Bookno<<" "<<total.sold<<" "<<total.revenue<<std::endl;
	}
	else
	{
		std::cerr<<"no data."<<std::endl;
		return -1;
	}
	return 0;
}
```
