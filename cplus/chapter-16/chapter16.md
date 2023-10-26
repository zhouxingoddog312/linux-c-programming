[toc]

### 16.1
使用模板实参代替模板参数来创建出模板的一个特定实例，即是实例化。
### 16.2
```c++
#include <cstring>
template <typename T> int compare(const T &v1,const T&v2)
{
	if(v1<v2)
		return -1;
	if(v2<v1)
		return 1;
	return 0;
}
template <unsigned M,unsigned N> int compare(const char (&p1)[M],const char (&p2)[N])
{
	return strcmp(p1,p2);
}
#include <iostream>
int main(void)
{
	std::cout<<compare(1,0)<<std::endl;
	std::cout<<compare("hi","hello")<<std::endl;
	return 0;
}
```
### 16.3
为什么能编译通过？
```
#include <cstring>
template <typename T> int compare(const T &v1,const T&v2)
{
	if(v1<v2)
		return -1;
	if(v2<v1)
		return 1;
	return 0;
}
template <unsigned M,unsigned N> int compare(const char (&p1)[M],const char (&p2)[N])
{
	return strcmp(p1,p2);
}
#include <iostream>
#include "./Sales_data.h"
int main(void)
{
	Sales_data s1("100-11",2,30),s2("100-12",5,20);
	std::cout<<s1<<std::endl;
	std::cout<<s2<<std::endl;
	std::cout<<compare(s1,s2)<<std::endl;
	return 0;
}
```
### 16.4
```
template <typename ITER,typename VAL> ITER find_hb(ITER beg,ITER end,const VAL &val)
{
	while(beg!=end)
	{
		if(*beg!=val)
			++beg;
		else
			break;
	}
	return beg;
}
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	vector<int> ivec{1,2,3,4,5};
	list<string> slist{"hi","hello","hei"};
	auto a=find_hb(ivec.begin(),ivec.end(),3);
	auto b=find_hb(slist.begin(),slist.end(),"hi");
	cout<<*a<<endl;
	cout<<*b<<endl;
	return 0;
}
```
### 16.5
```
#include <iostream>
template <unsigned N,typename T> void print(T (&arr)[N])
{
	for(const T &elem:arr)
		std::cout<<elem<<std::endl;
}
#include <string>
using std::string;
int main(void)
{
	string a[]={"hi","hello","hei"};
	print(a);
	return 0;
}
```
