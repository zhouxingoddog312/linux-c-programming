[toc]
### 11.1
&emsp;`map`中的元素是按 __关键字__ 和 __值__ 的方式**成对**保存的，值的访问也是依赖关键字。而vector中的元素是按它们在容器中的位置来顺序保存和访问的。
### 11.2
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
&emsp;需要按顺序访问及储存元素选择`list`，而需要快速判断该元素是否在集合中时选择`set`。
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
### 11.9
`map<string,list<unsigned>> word_rownum;`
### 11.10
&emsp;可以定义`vector<int>::iterator`到`int`的`map`，因为此类型的迭代器支持<操作；不能定义`list<int>::iterator`到`int`的`map`，因为此类型的迭代器不支持<操作。
### 11.11
`multiset<Sales_data,bool (*) (const Sales_data &,const Sales_data &)> bookstore(compareIsbn);`
### 11.12
```
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
using namespace std;
bool isnum(const string &s)
{
	istringstream is(s);
	double d;
	char c;
	if(!(is>>d))
		return false;
	if(is>>c)
		return false;
	return true;
}
int main(void)
{
	string stmp;
	vector<string> stmp_vec;
	int itmp;
	vector<int> itmp_vec;
	vector<pair<string,int>> pvec;
	cout<<"enter some string or int:";
	while(cin>>stmp)
	{
		if(isnum(stmp))
		{
			istringstream is(stmp);
			is>>itmp;
			itmp_vec.push_back(itmp);
		}
		else
			stmp_vec.push_back(stmp);
	}
	for(size_t index=0;index<stmp_vec.size()&&index<itmp_vec.size();++index)
	{
		pvec.push_back(pair<string,int>(stmp_vec[index],itmp_vec[index]));
	}
	for(const auto &p:pvec)
		cout<<p.first<<"	"<<p.second<<endl;
	return 0;
}
```
### 11.13
```
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
using namespace std;
bool isnum(const string &s)
{
	istringstream is(s);
	double d;
	char c;
	if(!(is>>d))
		return false;
	if(is>>c)
		return false;
	return true;
}
int main(void)
{
	string stmp;
	vector<string> stmp_vec;
	int itmp;
	vector<int> itmp_vec;
	vector<pair<string,int>> pvec;
	cout<<"enter some string or int:";
	while(cin>>stmp)
	{
		if(isnum(stmp))
		{
			istringstream is(stmp);
			is>>itmp;
			itmp_vec.push_back(itmp);
		}
		else
			stmp_vec.push_back(stmp);
	}
	for(size_t index=0;index<stmp_vec.size()&&index<itmp_vec.size();++index)
	{
		//pvec.push_back(pair<string,int>(stmp_vec[index],itmp_vec[index]));//第一种方法
		pvec.push_back({stmp_vec[index],itmp_vec[index]});//第二种方法
		//pvec.push_back(make_pair(stmp_vec[index],itmp_vec[index]));//第三种方法
	}
	for(const auto &p:pvec)
		cout<<p.first<<"	"<<p.second<<endl;
	return 0;
}
```
### 11.14
```
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
void addfamily(map<string,vector<pair<string,string>>> &fmap,const string &surname)
{
	fmap[surname];
}
void addchild(map<string,vector<pair<string,string>>> &fmap,const string &surname,const string &child,const string &birthday)
{
	fmap[surname].push_back({child,birthday});
}
int main(void)
{
	map<string,vector<pair<string,string>>> fmap;
	addfamily(fmap,"wang");
	addchild(fmap,"zhou","yi","1988.1.1");
	addchild(fmap,"zhou","er","1989.1.2");
	for(const auto &p1:fmap)
	{
		cout<<p1.first<<"家：";
		for(const auto &p2:p1.second)
			cout<<p2.first<<" "<<p2.second<<"	";
		cout<<endl;
	}
	return 0;
}
```
### 11.15
&emsp;对一个`int`到`vector<int>`的map，其`mapped_type`是`vector<int>`,`key_type`是`int`，`value_type`是`pair<const int,vector<int>>`。
### 11.16
`map<int,int>::iterator map_it=test_map.begin();map_it->second=value;`
### 11.17
`copy(v.begin(),v.end(),inserter(c,c.end()));`==合法==，调用multiset的insert成员函数，将vector中的元素，插入到c中。
`copy(v.begin(),v.end(),back_inserter(c));`==不合法==，因为multiset没有push_back成员函数。
`copy(c.begin(),c.end(),inserter(v,v.end()));`==合法==，调用vector的insert成员函数，将c中的元素插入v的末尾。
`copy(c.begin(),c.end(),back_inserter(v));`==合法==，调用vector的push_back成员函数，将c中的元素插入v的末尾。
### 11.18
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
	for(map<string,size_t>::iterator map_it=smp.begin();map_it!=smp.end();++map_it)
		cout<<map_it->first<<" occurs "<<map_it->second<<((map_it->second>1)?" times":" time")<<endl;
	return 0;
}
```
### 11.19
`multiset<Sales_data,bool (*)(const Sales_data &,const Sales_data &)>::iterator mlset_it=bookstore.begin();`
### 11.20
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
	{
		pair<map<string,size_t>::iterator,bool> ret=smp.insert({tmp,1});
		if(!ret.second)
			++ret.first->second;
	}
	for(auto &p:smp)
		cout<<p.first<<" occurs "<<p.second<<((p.second>1)?" times":" time")<<endl;
	return 0;
}
```
### 11.21
&emsp;word从标准输入读取字符串，并用word作为关键字，0作为值，构成pair插入word_count中。如果插入==成功==，则将插入的元素的值自增1.如果插入==不成功==则将相同关键字的值自增1.
### 11.22
`pair<map<string,vector<int>>::iterator,bool> insert(pair<string,vector<int>>);`
### 11.23
```
#include <iostream>
#include <map>
#include <string>
using namespace std;
void addchild(multimap<string,string> &smulmp,const string &surname,const string &child)
{
	smulmp.insert({surname,child});
}
void pt(multimap<string,string> &smulmp)
{
	for(auto it=smulmp.begin();it!=smulmp.end();++it)
		cout<<it->first<<" "<<it->second<<endl;
}
int main(void)
{
	multimap<string,string> familys;
	addchild(familys,"zhou","yi");
	addchild(familys,"wang","yi");
	addchild(familys,"zhou","er");
	pt(familys);
	return 0;
}
```
### 11.24
&emsp;如果关键字0在m中，则将其对应的值修改为1.如果关键字0不在m中，则向m中添加一个关键字为0，对应值为0的元素，然后将此元素的值修改为1.
### 11.25
&emsp;如果v中含有元素，则将v[0]赋值1.如果v是空的，则会产生严重错误。
### 11.26
可以用key_type类型对一个map进行下标操作，下标运算符返回的类型是mapped_type；例如`map<string,int>`，就可以用string类型对它进行下标操作，下标运算符返回的类型是int。
### 11.27
&emsp;只针对一个特定元素进行处理时，如在不允许重复关键字的关联容器中，选用find更合适。当要知道关联容器中有多少个元素的关键字与特定元素相等时，选用count。
### 11.28
`map<string,vector<int>>::iterator it=smap.find(key);`
### 11.29
&emsp;如果给定关键字不在容器中，`upper_bound`与`lower_bound`会返回相同的迭代器，迭代器会指向第一个不影响排序的关键字插入位置，而`equal_range`会返回一个`pair`类型的对象，其`first`成员和`second`成员都会指向第一个不影响排序的关键字插入位置。
### 11.30
&emsp;pos是`equal_range`返回的`pair`对象，pos的`first`成员是指向第一个匹配search_item关键字的`map`中的元素，而该元素的`second`成员，即pos.first->second则是关联容器中search_item关键字对应的值。
### 11.31
```
#include <iostream>
#include <map>
#include <string>
using namespace std;
void addbook(multimap<string,string> &books,const string &literature,const string &author)
{
	books.insert({literature,author});
}
void delbook(multimap<string,string> &books,const string &literature)
{
	auto it=books.find(literature);
	if(it==books.end())
		cout<<"Can't find the book "<<literature<<endl;
	else
	{
		books.erase(it);
		cout<<"The book "<<literature<<" is removed"<<endl;
	}
}
void printbook(const multimap<string,string> &books)
{
	for(auto it=books.begin();it!=books.end();++it)
		cout<<"author: "<<it->second<<" literature: "<<it->first<<endl;
}
int main(void)
{
	string liter,auth;
	multimap<string,string> books;
	cout<<"Enter literature and author(q to quit):";
	while(cin>>liter&&liter!="q")
	{
		cin>>auth;
		addbook(books,liter,auth);
	}
	cout<<"Enter literature to delete(q to quit):";
	while(cin>>liter&&liter!="q")
		delbook(books,liter);
	printbook(books);
	return 0;
}
```
### 11.32
```
#include <iostream>
#include <map>
#include <string>
using namespace std;
void addbook(multimap<string,string> &books,const string &author,const string &literature)
{
	books.insert(make_pair(author,literature));
}
void delbook(multimap<string,string> &books,const string &author,const string &literature)
{
	pair<multimap<string,string>::iterator,multimap<string,string>::iterator> pair_it=books.equal_range(author);
	if(pair_it.first==pair_it.second)
		cout<<"There is no author named "<<author<<endl;
	else
	{
		for(auto beg=pair_it.first,ed=pair_it.second;beg!=ed;++beg)
		{
			if(beg->second==literature)
			{
				books.erase(beg);
				cout<<"The literature "<<literature<<" writed by "<<author<<" was deleted"<<endl;
				return;
			}
		}
		cout<<"There is no book named "<<literature<<" writed by "<<author<<endl;
	}
}
void printbook(const multimap<string,string> &books)
{
	for(auto it=books.begin();it!=books.end();++it)
		cout<<"author: "<<it->first<<" literature: "<<it->second<<endl;
}
int main(void)
{
	multimap<string,string> books;
	string auth,liter;	
	cout<<"Enter author and literature(q to quit):";
	while(cin>>auth&&auth!="q")
	{
		cin>>liter;
		addbook(books,auth,liter);
	}
	cout<<"Enter author and literature to delete(q to quit):";
	while(cin>>auth&&auth!="q")
	{
		cin>>liter;
		delbook(books,auth,liter);
	}
	printbook(books);
	return 0;
}
```
### 11.33
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
using namespace std;
map<string,string> buildMap(ifstream &map_file)
{
	map<string,string> trans_map;
	string key,value;
	while(map_file>>key&&getline(map_file,value))
	{
		if(value.size()>1)
			trans_map[key]=value.substr(1);
		else
			throw runtime_error("no rule for "+key);
	}
	return trans_map;
}
const string & transform(const string &str,map<string,string> &m)
{
	auto map_it=m.find(str);
	if(map_it==m.end())
		return str;
	else
		return map_it->second;
}
void word_transform(ifstream &map_file,ifstream &input)
{
	auto trans_map=buildMap(map_file);
	string text;
	while(getline(input,text))
	{
		istringstream stream(text);
		string word;
		bool firstword=true;
		while(stream>>word)
		{
			if(firstword)
				firstword=false;
			else
				cout<<" ";
			cout<<transform(word,trans_map);
		}
		cout<<endl;
	}
}
int main(int argc,char *argv[])//第一个参数是map文件，第二个参数是源文本文件
{
	ifstream map_file(argv[1]);
	ifstream input(argv[2]);
	word_transform(map_file,input);
	return 0;
}
```
### 11.34
&emsp;如果map中含有该关键字，那么行为与原来的一样，如果map中不含该关键字，则会返回一个空的字符串。
### 11.35
&emsp;如果map中没有该关键字，那么前后行为一致。如果map中含有该关键字，那么下标操作会改变该关键字对应的值，而insert操作则什么都不做，并返回一个pair对象。该pair对象的first成员为指向现有关键字的迭代器，而second成员则是一个值为false的bool量，代表插入不成功。
### 11.36
&emsp;书中程序处理了这种情况的，如果文件中的某一行包含一个关键字和一个空格，那么这一行的转换规则不会录入map。
### 11.37
&emsp;在关键字类型的元素**没有**明显的序关系的情况下，使用无序容器，通常性能更好。而有序容器的优势在于维护了关键字的序。
### 11.38
```
//单词计数程序
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int main(void)
{
	unordered_map<string,size_t> word_count;
	string tmp;
	while(cin>>tmp)
		++word_count[tmp];
	for(const auto &elemt:word_count)
	{
		cout<<elemt.first<<" occurs "<<elemt.second<<(elemt.second>1?" times":" time")<<endl;
	}
	return 0;
}
//单词转换程序
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdexcept>
using namespace std;
unordered_map<string,string> buildMap(ifstream &map_file)
{
	unordered_map<string,string> trans_map;
	string key,value;
	while(map_file>>key&&getline(map_file,value))
	{
		if(value.size()>1)
			trans_map[key]=value.substr(1);
		else
			throw runtime_error("no rule for "+key);
	}
	return trans_map;
}
const string & transform(const string &str,unordered_map<string,string> &m)
{
	auto map_it=m.find(str);
	if(map_it==m.end())
		return str;
	else
		return map_it->second;
}
void word_transform(ifstream &map_file,ifstream &input)
{
	auto trans_map=buildMap(map_file);
	string text;
	while(getline(input,text))
	{
		istringstream stream(text);
		string word;
		bool firstword=true;
		while(stream>>word)
		{
			if(firstword)
				firstword=false;
			else
				cout<<" ";
			cout<<transform(word,trans_map);
		}
		cout<<endl;
	}
}
int main(int argc,char *argv[])//第一个参数是map文件，第二个参数是源文本文件
{
	ifstream map_file(argv[1]);
	ifstream input(argv[2]);
	word_transform(map_file,input);
	return 0;
}
```
