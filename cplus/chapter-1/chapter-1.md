[toc]
###1.1
```
int main()
{
	return 0;
}
```
### 1.2
```
int main()
{
	return -1;
}
```
###1.3
```
#include <iostream>
int main()
{
	std::cout<<"Hello World!"<<std::endl;
	return 0;
}
```
###1.4
```
#include <iostream>
int main()
{
	std::cout<<"Enter two numbers:"<<std::endl;
	int v1=0,v2=0;
	std::cin>>v1>>v2;
	std::cout<<"The product of "<<v1<<" and "<<v2<<" is "<<v1*v2<<std::endl;
	return 0;
}
```
###1.5
```
#include <iostream>
int main()
{
	std::cout<<"Enter two numbers:";
	std::cout<<std::endl;
	int v1=0,v2=0;
	std::cin>>v1>>v2;
	std::cout<<"The product of ";
	std::cout<<v1;
	std::cout<<" and ";
	std::cout<<v2;
	std::cout<<" is ";
	std::cout<<v1*v2;
	std::cout<<std::endl;
	return 0;
}
```
###1.6
&emsp;==不==合法，因为第二三行缺乏输出运算符的左侧运算对象。
应该修改为：
std::cout<<"The sum of "<<v1;
std::cout<<" and "<<v2;
std::cout<<" is "<<v1+v2<<std::endl;
###1.7
```
#include <iostream>
int main()
{
	std::cout<<"Enter two numbers:";
	std::cout<<std::endl;
	/*这是一个嵌套注释的程序
	 * 我们来看看/**/
	 *编译后
	 *的错误提示
	 */
	int v1=0,v2=0;
	std::cin>>v1>>v2;
	std::cout<<"The product of ";
	std::cout<<v1;
	std::cout<<" and ";
	std::cout<<v2;
	std::cout<<" is ";
	std::cout<<v1*v2;
	std::cout<<std::endl;
	return 0;
}
```
###1.8
```
#include <iostream>
int main()
{
	//只有第三行的错误的
	std::cout<<"/*";
	std::cout<<"*/";
	//std::cout<</*"*/"*/;
	std::cout<</**/"*/";//上一行的更正
	std::cout<</* "*/" /* "/*"  */;
	return 0;
}
```
###1.9
```
#include <iostream>
int main()
{
	int sum=0,val=50;
	while(val<=100)
	{
		sum+=val;
		val++;
	}
	std::cout<<"Sum of 50 to 100 inclusive is "<<sum<<std::endl;
	return 0;
}
```
###1.10
```
#include <iostream>
int main()
{
	int val=10;
	while(val>=0)
	{
		std::cout<<val<<std::endl;
		--val;
	}
	return 0;
}
```
###1.11
```
#include <iostream>
int main()
{
	int val1,val2,tmp;
	std::cout<<"Enter two integer:";
	std::cin>>val1>>val2;
	if(val1<val2)
	{
		tmp=val1;
		val1=val2;
		val2=tmp;
	}
	std::cout<<"Print total numbers in the range from "<<val1<<" to "<<val2<<std::endl;
	while(val1>=val2)
	{
		std::cout<<val1<<" ";
		val1--;
	}
	std::cout<<std::endl;
	return 0;
}
```
###1.12
&emsp;for循环完成从-100累加到100，sum的终值是0。
###1.13
```
#include <iostream>
int main()
{
	for(int val=10;val>=0;val--)
		std::cout<<val<<std::endl;
	return 0;
}
#include <iostream>
int main()
{
	int val1,val2,tmp;
	std::cout<<"Enter two integer:";
	std::cin>>val1>>val2;
	if(val1<val2)
	{
		tmp=val1;
		val1=val2;
		val2=tmp;
	}
	std::cout<<"Print total numbers in the range from "<<val1<<" to "<<val2<<std::endl;
	for(;val1>=val2;val1--)
		std::cout<<val1<<" ";
	std::cout<<std::endl;
	return 0;
}
#include <iostream>
int main()
{
	int sum=0;
	for(int val=50;val<=100;val++)
		sum+=val;
	std::cout<<"Sum of 50 to 100 inclusive is "<<sum<<std::endl;
	return 0;
}
```
###1.14
&emsp;while 循环的 __优点__ 是书写简单，__缺点__ 是程序员可能忘记在循环体（statement）内作用条件判断语句（condition），造成无限循环；for 循环的 __优点__ 是规范、整洁，不易漏掉作用条件判断（condition）的表达式（expression），__缺点__ 是书写稍繁琐。while 循环适合循环次数不确定的情景；for 循环适合循环次数事先已知。
###1.15
```
#include <iostream>
int main()
{
	std::cout<<"Read each file."<<std::endl:
	std::cout<< Update master. <<std::endl;
	std::cout<<"Write new master." std::endl;
	return 0
}
```
###1.16
```
#include <iostream>
int main()
{
	int sum=0,value=0;
	while(std::cin>>value)
		sum+=value;
	std::cout<<"The sum is "<<sum<<"."<<std::endl;
	return 0;
}
```
###1.17
&emsp;如果输入的所有值都相等，本节程序会输出该值出现多少次。如果没有重复值，输出会是每个值出现一次。
###1.18
- 所有值都**相等**
1 1 1 1 1
1 occurs 5 time.
- **没有**重复值
1 2 3
1 occurs 1 times.
2 occurs 1 times.
3 occurs 1 time.
###1.19
```
#include <iostream>
int main()
{
	int val1,val2,tmp;
	std::cout<<"Enter two integer:";
	std::cin>>val1>>val2;
	if(val1<val2)//处理用户输入的第一个数比第二个数小的情况
	{
		tmp=val1;
		val1=val2;
		val2=tmp;
	}
	std::cout<<"Print total numbers in the range from "<<val1<<" to "<<val2<<std::endl;
	while(val1>=val2)
	{
		std::cout<<val1<<" ";
		val1--;
	}
	std::cout<<std::endl;
	return 0;
}
```
###1.20
```
#include <iostream>
#include "Sales_item.h"
int main()
{
	Sales_item tmp;
	while(std::cin>>tmp)
		std::cout<<tmp<<std::endl;
	return 0;
}
```
###1.21
```
#include <iostream>
#include "Sales_item.h"
int main()
{
	Sales_item result,tmp;
	std::cin>>result>>tmp;
	std::cout<<result+tmp<<std::endl;
	return 0;
}
```
###1.22
```
#include <iostream>
#include "Sales_item.h"
int main()
{
	Sales_item result,tmp;
	std::cin>>result;
	while(std::cin>>tmp)
		result+=tmp;
	std::cout<<result<<std::endl;
	return 0;
}
```
###1.23
```
#include <iostream>
#include "Sales_item.h"
int main()
{
	Sales_item current_item,next_item;
	if(std::cin>>current_item)
	{
		int cnt=1;
		while(std::cin>>next_item)
		{
			if(current_item.isbn()==next_item.isbn())
			{
				current_item+=next_item;
				cnt++;
			}
			else
			{
				std::cout<<current_item<<" ocurrs "<<cnt<<" times."<<std::endl;
				current_item=next_item;
				cnt=1;
			}
		}
		std::cout<<current_item<<" ocurrs "<<cnt<<" times."<<std::endl;
	}
	return 0;
}
```
###1.24
**运行结果:**
>0-201-78345-X 4 25.0
0-201-78345-X 1 25.0
0-201-78345-X 2 25.0
0-201-78345-X 9 25.0
0-207-78345-X 9 31.0
0-207-78345-X 3 31.0
0-202-78345-X 3 20.0
0-202-78345-X 3 20.0
###1.25
```
#include <iostream>
#include "Sales_item.h"
int main()
{
	Sales_item total;
	if(std::cin>>total)
	{
		Sales_item trans;
		while(std::cin>>trans)
		{
			if(total.isbn()==trans.isbn())
				total+=trans;
			else
			{
				std::cout<<total<<std::endl;
				total=trans;
			}
		}
		std::cout<<total<<std::endl;
	}
	else
	{
		std::cerr<<"No data?"<<std::endl;
		return -1;
	}
	return 0;
}
```
**运行结果:**
>0-201-78345-X 16 400 25
0-207-78345-X 12 372 31
0-202-78345-X 6 120 20
