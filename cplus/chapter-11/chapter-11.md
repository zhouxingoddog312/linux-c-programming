[toc]
###11.1
map中的元素是按关键字和值的方式成对保存的，值的访问也是依赖关键字。而vector中的元素是按它们在容器中的位置来顺序保存和访问的。
###11.2
- vector,一般在末尾作添加删除，元素数量变化不大，需要随机访问。
- deque，以上条件下，如果还需要在头部频繁添加删除元素，可以选择。
- list，元素较多，元素数量在程序运行中变化频繁，只采用遍历的方式访问元素。
- map，有关联的许多对关键字和值。
- set，保存许多同类型元素的集合，并按值访问。
###11.3
```
#include <iostream>
#include <map>
#include <string>
using namespace std;
int main(void)
{
	string tmp;
	map<string,size_t> smp;
	while(cin>>tmp)
		++smp[tmp];
	for(auto &p:smp)
		cout<<p.first<<" occurs "<<p.second<<((p.second>1)?" times":" time")<<endl;
	return 0;
}
```
###11.4
```
#include <iostream>
#include <map>
#include <string>
#include <cctype>
using namespace std;
int main(void)
{
	string tmp;
	map<string,size_t> smp;
	while(cin>>tmp)
	{
		for(size_t index=0;index<tmp.size();)
		{
			tmp[index]=tolower(tmp[index]);
			if(ispunct(tmp[index]))
				tmp.erase(index,1);
			else
				index++;
		}
		++smp[tmp];
	}
	for(auto &p:smp)
		cout<<p.first<<" occurs "<<p.second<<((p.second>1)?" times":" time")<<endl;
	return 0;
}
```
###11.5
&emsp;map存储的是键值对，而set只存储关键字，所以需要依据关键字查找对应值时使用map，而只需要单纯检查关键字是否存在时选用set。
###11.6
&emsp;需要按顺序访问及储存元素选择list，而需要快速判断该元素是否在集合中时选择set。
###11.7
```
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
void addfamily(map<string,vector<string>> &fmap,const string &surname)
{
	fmap[surname];
}
void addchild(map<string,vector<string>> &fmap,const string &surname,const string &child)
{
	fmap[surname].push_back(child);
}
int main(void)
{
	map<string,vector<string>> fmap;
	addfamily(fmap,"wang");
	addchild(fmap,"zhou","yi");
	addchild(fmap,"zhou","er");
	for(const auto &p1:fmap)
	{
		cout<<p1.first<<"家：";
		for(const auto &p2:p1.second)
			cout<<p2<<" ";
		cout<<endl;
	}
	return 0;
}
```
###11.8
```
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<string>::iterator save_word(vector<string> &svec,const string &str)
{
	vector<string>::iterator svec_it=find(svec.begin(),svec.end(),str);
	if(svec_it==svec.end())
	{
		svec.push_back(str);
		return svec.end()-1;
	}
	else
		return svec_it;
}//返回值为指向插入或已存在单词的迭代器
int main(void)
{
	string tmp;
	vector<string> svec;
	while(cin>>tmp)
		save_word(svec,tmp);
	for(const auto &p:svec)
		cout<<p<<" ";
	cout<<endl;
	return 0;
}
```
&emsp;使用vector要保存不重复的单词，需要利用泛型算法排除重复项，而set则由模板自己完成这项工作。
