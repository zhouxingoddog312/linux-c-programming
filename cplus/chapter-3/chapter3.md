[toc]
### 3.1
==1.cpp==
```
#include <iostream>
using std::cout;
using std::endl;
int main()
{
	int sum=0,val=50;
	while(val<=100)
	{
		sum+=val;
		val++;
	}
	cout<<"Sum of 50 to 100 inclusive is "<<sum<<endl;
	return 0;
}
```
==2.cpp==
```
#include <iostream>
using std::cout;
using std::endl;
int main()
{
	int val=10;
	while(val>=0)
	{
		cout<<val<<endl;
		--val;
	}
	return 0;
}
```
==3.cpp==
```
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main()
{
	int val1,val2,tmp;
	cout<<"Enter two integer:";
	cin>>val1>>val2;
	if(val1<val2)
	{
		tmp=val1;
		val1=val2;
		val2=tmp;
	}
	cout<<"Print total numbers in the range from "<<val1<<" to "<<val2<<endl;
	while(val1>=val2)
	{
		cout<<val1<<" ";
		val1--;
	}
	cout<<endl;
	return 0;
}
```
==4.cpp==
```
#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
struct Sales_data
{
	string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data temp;
	double price=0.0;
	while(cin>>temp.Bookno)
	{
		cin>>temp.sold>>price;
		temp.revenue=temp.sold*price;
		cout<<temp.Bookno<<" "<<temp.sold<<" "<<temp.revenue<<endl;
		price=0;
	}
	return 0;
}
```
==5.cpp==
```
#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
struct Sales_data
{
	string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
int main()
{
	Sales_data temp1,temp2;
	double price=0;
	cin>>temp1.Bookno>>temp1.sold>>price;
	temp1.revenue=temp1.sold*price;
	price=0;
	cin>>temp2.Bookno>>temp2.sold>>price;
	temp2.revenue=temp2.sold*price;
	if(temp1.Bookno==temp2.Bookno)
		cout<<temp1.Bookno<<" "<<temp1.sold+temp2.sold<<" "<<temp1.revenue+temp2.revenue<<endl;
	else
		cerr<<"not the same isbn";
	return 0;
}
```
==6.cpp==
```
#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
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
==7.cpp==
```
#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
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
### 3.2
==3-2-1.cpp==
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string line;
	while(getline(cin,line))
		cout<<line<<endl;
	return 0;
}
```
==3-2-2.cpp==
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string line;
	while(cin>>line)
		cout<<line<<endl;
	return 0;
}
```
### 3.3
&emsp;&emsp;**string**类的输入运算符会忽略空白，**getline**函数会存储空白。
### 3.4
==3-4-1.cpp==
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string st1,st2;
	while(cin>>st1>>st2)
	{
		if(st1>st2)
			cout<<st1<<endl;
		else if(st1<st2)
			cout<<st2<<endl;
	}
	return 0;
}
```
==3-4-2.cpp==
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string st1,st2;
	while(cin>>st1>>st2)
	{
		if(st1.size()>st2.size())
			cout<<st1<<endl;
		else if(st1.size()<st2.size())
			cout<<st2<<endl;
	}
	return 0;
}
```
### 3.5
==3-5-1.cpp==
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string st1,st2,st3;
	cin>>st1>>st2>>st3;
	cout<<st1+st2+st3<<endl;
	return 0;
}
```
==3-5-2.cpp==
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string st1,st2,st3;
	cin>>st1>>st2>>st3;
	cout<<st1+' '+st2+' '+st3<<endl;
	return 0;
}
```
### 3.6
```
#include <iostream>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string s("Hello World!!!");
	for(auto &c:s)
		c='X';
	cout<<s<<endl;
	return 0;
}
```
### 3.7
一样的
```
#include <iostream>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string s("Hello World!!!");
	for(char &c:s)
		c='X';
	cout<<s<<endl;
	return 0;
}
```
### 3.8
==3-8-1.cpp==
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main(void)
{
	string str="Hello World!!!";
	decltype(str.size()) index=0;
	for(;index!=str.size();index++)
		str[index]='X';
	cout<<str<<endl;
	return 0;
}
```
==3-8-2.cpp==
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main(void)
{
	string str="Hello World!!!";
	decltype(str.size()) index=0;
	while(index!=str.size())
	{
		str[index++]='X';
	}
	cout<<str<<endl;
	return 0;
}
```
### 3.9
&emsp;&emsp;不合法，使用下标访问空**string**的行为未定义。
### 3.10
```
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main(void)
{
	string trans,result;
	while(cin>>trans)
	{
		for(auto c:trans)
		{
			if(!ispunct(c))
				result+=c;
		}
		cout<<result<<endl;
		result="";
	}
	return 0;
}
```
### 3.11
合法，`c`的类型是`const char &`。
### 3.12
1. 正确，`vector`包含的元素是`vector<int>`。
2. 不正确，`vector`的元素类型不同。
3. 正确，`vector`中含有10个**null**字符串。
### 3.13
1. 空
2. 10个0
3. 10个42
4. 1个10
5. 10、42
6. 10个空的`string`
7. 10个**hi**字符串
### 3.14
```
#include <iostream>
#include <vector>
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<int> ivec;
	int temp;
	while(cin>>temp)
	{
		ivec.push_back(temp);
	}
	return 0;
}
```
### 3.15
```
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<string> svec;
	string temp;
	while(cin>>temp)
	{
		svec.push_back(temp);
	}
	return 0;
}
```
### 3.16
```
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10,42);
	vector<int> v4{10};
	vector<int> v5{10,42};
	vector<string> v6{10};
	vector<string> v7{10,"hi"};
	
	cout<<"v1";
	if(v1.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto a:v1)
			cout<<" "<<a;
		cout<<endl;
	}

	cout<<"v2";
	if(v2.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto b:v2)
			cout<<" "<<b;
		cout<<endl;
	}

	cout<<"v3";
	if(v3.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto c:v3)
			cout<<" "<<c;
		cout<<endl;
	}	
	
	cout<<"v4";
	if(v4.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto d:v4)
			cout<<" "<<d;
		cout<<endl;
	}
	cout<<"v5";
	if(v5.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto e:v5)
			cout<<" "<<e;
		cout<<endl;
	}
	cout<<"v6";
	if(v6.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto f:v6)
			cout<<" "<<f;
		cout<<endl;
	}
	cout<<"v7";
	if(v7.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto g:v7)
			cout<<" "<<g;
		cout<<endl;
	}

	return 0;
}
```
### 3.17
```
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<string> svec;
	string tmp;
	while(cin>>tmp)
		svec.push_back(tmp);
	for(auto &a:svec)
	{
		for(auto &b:a)
			b=toupper(b);
	}
	for(auto c:svec)
		cout<<c<<endl;
	return 0;
}
```
### 3.18
**不合法**
```
vector<int> ivec;
ivec.push_back(42);
```
### 3.19
```
vector<int> ivec(10,42);
vector<int> ivec{42,42,42,42,42,42,42,42,42,42};
vector<int> ivec={42,42,42,42,42,42,42,42,42,42};
```
### 3.20
==3-20-1.cpp==
```
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<int> ivec;
	int tmp;
	while(cin>>tmp)
		ivec.push_back(tmp);
	for(decltype(ivec.size())index=0;index<ivec.size()-1;index+=2)
		cout<<ivec[index]+ivec[index+1]<<endl;
	return 0;
}
```
==3-20-2.cpp==
```
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<int> ivec;
	int tmp;
	while(cin>>tmp)
		ivec.push_back(tmp);
	for(decltype(ivec.size())head=0,tail=ivec.size()-1;head<tail;head+=1,tail-=1)
		cout<<ivec[head]+ivec[tail]<<endl;
	return 0;
}
```
### 3.21
```
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10,42);
	vector<int> v4{10};
	vector<int> v5{10,42};
	vector<string> v6{10};
	vector<string> v7{10,"hi"};
	
	cout<<"v1";
	if(v1.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto a=v1.cbegin();a!=v1.cend();a++)
			cout<<" "<<*a;
		cout<<endl;
	}

	cout<<"v2";
	if(v2.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto b=v2.cbegin();b!=v2.cend();b++)
			cout<<" "<<*b;
		cout<<endl;
	}

	cout<<"v3";
	if(v3.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto c=v3.cbegin();c!=v3.cend();c++)
			cout<<" "<<*c;
		cout<<endl;
	}	
	
	cout<<"v4";
	if(v4.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto d=v4.cbegin();d!=v4.cend();d++)
			cout<<" "<<*d;
		cout<<endl;
	}
	cout<<"v5";
	if(v5.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto e=v5.cbegin();e!=v5.cend();e++)
			cout<<" "<<*e;
		cout<<endl;
	}
	cout<<"v6";
	if(v6.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto f=v6.cbegin();f!=v6.cend();f++)
			cout<<" "<<*f;
		cout<<endl;
	}
	cout<<"v7";
	if(v7.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto g=v7.cbegin();g!=v7.cend();g++)
			cout<<" "<<*g;
		cout<<endl;
	}

	return 0;
}
```
### 3.22
```
for(auto it=text.begin();it!=text.end()&&!it->empty();it++)
{
	for(auto pts=it->begin();pts!=it->end();pts++)
		*pts=toupper(*pts);
	cout<<*it<<endl;
}
```
### 3.23
```
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main(void)
{
	vector<int> ivec(10,21);
	for(auto it=ivec.begin();it!=ivec.end();it++)
	{
		(*it)*=2;
		cout<<*it<<" ";
	}
	cout<<endl;
	return 0;
}
```
### 3.24
==3-24-1.cpp==
```
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<int> ivec;
	int tmp;
	while(cin>>tmp)
		ivec.push_back(tmp);
	for(auto it=ivec.begin();it<ivec.end()-1;it+=2)
		cout<<*it+*(it+1)<<" ";
	cout<<endl;
	return 0;
}
```
==3-24-2.cpp==
```
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<int> ivec;
	int tmp;
	while(cin>>tmp)
		ivec.push_back(tmp);
	for(auto beg=ivec.begin(),end=ivec.end()-1;beg<end;beg+=1,end-=1)
		cout<<*beg+*end<<" ";
	cout<<endl;
	return 0;
}
```
### 3.25
```
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<unsigned> scores(11,0);
	unsigned grade;
	auto beg=scores.begin();
	while(cin>>grade)
	{
		if(grade<=100)
			(*(beg+grade/10))++;
	}
	for(decltype(scores.size())index=0;index!=scores.size();index++)
	{
		if(index<scores.size()-1)
			cout<<scores[index]<<" ";
		else
			cout<<scores[index]<<endl;
	}
	return 0;
}
```
### 3.26
&emsp;&emsp;不能将两个迭代器相加。
### 3.27
1. 不合法，数组的维度必须是常量表达式。
2. 合法
3. 不合法，数组的维度必须是常量表达式。
4. 不合法，字符数组长度不够。
### 3.28
```
string sa[10];//10个空字符串
int ia[10];//10个0
int main(){
    string sa2[10];//10个空字符串
    int ia2[10];//10个未初始化的值
}
```
### 3.29
&emsp;&emsp;**数组**与`vector`的==相似==之处是都能存放类型相同的对象，且这些对象本身没有名字，需要通过其所在位置访问。
&emsp;&emsp;**数组**与`vector`的最大==不同==是，数组的大小固定不变，不能随意向数组中增加额外的元素，虽然在某些情境下运行时性能较好，但是与vector相比损失了灵活性。
&emsp;&emsp;具体来说，数组的维度在定义时已经确定，如果我们想更改数组的长度，只能创建一个更大的新数组，然后把原数组的所有元素复制到新数组中去。数组也无法像vector那样使用size函数直接获取数组的维度。如果是字符数组，可以调用 strlen 函数得到字符串的长度；如果是其他数组，只能使用`sizeof(array) / sizeof(array[0])`的方式计算数组的维度。
### 3.30
&emsp;&emsp;遍历维度为10的数组，下标应该是==从0到9==.
### 3.31
```
#include <iostream>
#include <cstddef>
using std::cout;
using std::endl;
int main()
{
	int arr[10];
	for(size_t index=0;index<10;index++)
		arr[index]=index;
	for(auto value:arr)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
```
### 3.32
==3-32-1.cpp==
```
#include <iostream>
#include <cstddef>
using std::cout;
using std::endl;
int main()
{
	int arr_1[10];
	int arr_2[10];
	for(size_t index=0;index<10;index++)
	{
		arr_1[index]=index;
		arr_2[index]=arr_1[index];
	}
	for(auto value:arr_2)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
```
==3-32-2.cpp==
```
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<int> ivec1(10,0);
	for(decltype(ivec1.size())index=0;index!=ivec1.size();index++)
		ivec1[index]=index;
	vector<int> ivec2=ivec1;
	for(auto value:ivec2)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
```
### 3.33
&emsp;&emsp;因为数组定义在**函数内部**，且数组元素是**内置类型**，所以数组内元素此时都是==未定义的值== 。
### 3.34
&emsp;&emsp;指针p1前进到p2所在的位置，指向同一个元素。p1、p2两个指针类型不同时，该程序非法。
### 3.35
```
#include <iostream>
#include <iterator>
using std::cout;
using std::endl;
using std::begin;
using std::end;
int main()
{
	int arr[10];
	for(int *pbeg=begin(arr),*pend=end(arr);pbeg!=pend;pbeg++)
		*pbeg=0;
	for(auto value:arr)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
```
### 3.36
```
#include <iostream>
#include <vector>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::begin;
using std::end;
int main()
{
	int arr1[]={1,2,3,4,5};
	int arr2[]={0,0,0,0,0};
	vector<int> ivec1{0,0,0,0,0};
	vector<int> ivec2(5,0);
	for(size_t index=0;index<5;index++)
	{
		if(arr1[index]!=arr2[index])
			goto wrong;
	}
	cout<<"Two array are equality."<<endl;
	if(ivec1==ivec2)
		cout<<"Two vector are equality."<<endl;
	else
		cout<<"Two vector are not equality."<<endl;
	return 0;

wrong:	cout<<"Two array are not equality."<<endl;
	if(ivec1==ivec2)
		cout<<"Two vector are equality."<<endl;
	else
		cout<<"Two vector are not equality."<<endl;
	return 0;
}
```
### 3.37
&emsp;&emsp;程序希望逐个输出==hello==，但是字符数组**ca**并没有以`'\0'`结尾，所以`while`循环无法结束。
### 3.38
&emsp;&emsp;指针本身的值是一个内存**地址值**，表示指针所指对象在内存中的**存储地址**。如果我们把两个指针加在一起，就是试图把内存中两个对象的存储地址加在一起，这显然是没有任何意义的。
### 3.39
```
#include <iostream>
#include <string>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string str1{"Hello World"},str2("Hello World");
	if(str1==str2)
		cout<<"Two strings are equality."<<endl;
	char str3[]="Hello World";
	char str4[]="hello world";
	if(strcmp(str3,str4)==0)
		cout<<"Two c style strings are equality."<<endl;
	else if(strcmp(str3,str4)>0)
		cout<<"str3 > str4"<<endl;
	else
		cout<<"str3 < str4"<<endl;
	return 0;
}
```
### 3.40
```
#include <iostream>
#include <string>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	char str1[]="Hello";
	char str2[]="World";
	char str3[12]="";
	strcpy(str3,str1);
	strcat(str3," ");
	strcat(str3,str2);
	cout<<str3<<endl;
	return 0;
}
```
### 3.41
```
#include <iostream>
#include <random>
#include <vector>
#include <iterator>
using namespace std;
int main()
{
	int arr[10];
	default_random_engine rad;
	for(size_t index=0;index<10;index++)
		arr[index]=rad()%20;
	vector<int> ivec(begin(arr),end(arr));
	for(auto value:ivec)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
```
### 3.42
```
#include <iostream>
#include <vector>
#include <random>
using namespace std;
int main()
{
	default_random_engine rad;
	uniform_int_distribution<int> u(-10,10);
	size_t index;
	vector<int> ivec;
	int arr[10];
	for(index=0;index<10;index++)
		ivec.push_back(u(rad));
	cout<<"there are the vector: ";
	for(auto value:ivec)
		cout<<value<<" ";
	cout<<endl;
	for(index=0;index<10;index++)
		arr[index]=ivec[index];
	cout<<"There are the values of array: ";
	for(index=0;index<10;index++)
		cout<<arr[index]<<" ";
	cout<<endl;
	return 0;
}
```
### 3.43
==3-43-1.cpp==
```
#include <iostream>
using namespace std;
int main()
{
	int ia[3][4]=
	{
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11}
	};
	for(int (&a)[4]:ia)
		for(int b:a)
			cout<<b<<" ";
	cout<<endl;
	return 0;
}
```
==3-43-2.cpp==
```
#include <iostream>
using namespace std;
int main()
{
	int ia[3][4]=
	{
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11}
	};
	size_t x,y;
	for(x=0;x<3;x++)
		for(y=0;y<4;y++)
			cout<<ia[x][y]<<" ";
	cout<<endl;
	return 0;
}
```
==3-43-3.cpp==
```
#include <iostream>
using namespace std;
int main()
{
	int ia[3][4]=
	{
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11}
	};
	int (*p) [4],*q;
	for(p=ia;p<ia+3;p++)
		for(q=*p;q<*p+4;q++)
			cout<<*q<<" ";
	cout<<endl;
	return 0;
}
```
### 3.44
```
#include <iostream>
using namespace std;
typedef int int_array[4];
int main()
{
	int ia[3][4]=
	{
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11}
	};
	int_array *p;
	int *q;
	for(p=ia;p<ia+3;p++)
		for(q=*p;q<*p+4;q++)
			cout<<*q<<" ";
	cout<<endl;
	return 0;
}
```
### 3.45
```
#include <iostream>
using namespace std;
int main()
{
	int ia[3][4]=
	{
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11}
	};
	for(auto &a:ia)
		for(auto b:a)
			cout<<b<<" ";
	cout<<endl;
	return 0;
}
```
