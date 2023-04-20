[toc]
###10.1
```
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;
int main(void)
{
	vector<int> ivec;
	int itmp;
	int targ=0;
	cout<<"Enter some integer(q to quit): ";
	while(cin>>itmp)
		ivec.push_back(itmp);
	cout<<"Which target do you count: ";
	cin.clear();
	cin.ignore(INT_MAX,'\n');
	cin>>targ;
	itmp=0;
	itmp=count(ivec.begin(),ivec.end(),targ);
	cout<<itmp<<" targets are find."<<endl;
	return 0;
}
```
###10.2
```
#include <iostream>
#include <algorithm>
#include <list>
#include <string>
using namespace std;
int main(void)
{
	list<string> slst;
	string stmp;
	cout<<"Enter some strings: ";
	while(cin>>stmp&&stmp!="quit")
		slst.push_back(stmp);
	cout<<"Which string do you want to count: ";
	cin>>stmp;
	cout<<stmp<<" occurs "<<count(slst.begin(),slst.end(),stmp)<<" times."<<endl;
	return 0;
}
```
###10.3
```
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
int main(void)
{
	int tmp,sum=0;
	vector<int> ivec;
	cout<<"Enter some integers(q to quit): ";
	while(cin>>tmp)
		ivec.push_back(tmp);
	sum=accumulate(ivec.cbegin(),ivec.cend(),0);
	cout<<"Sum is "<<sum<<endl;
	return 0;
}
```
###10.4
&emsp;`accumulate`的第三个参数是和的初值，它还决定了函数的返回类型以及函数中使用哪个加法运算符，所以本题中和的初始是整型，则会发生双精度浮点数向整型的转换，损失小数点后的部分。
###10.5
&emsp;`equal`使用`==`运算符比较两个序列中的元素。`string`类重载了`==`运算符，可以比较两个`string`或者一个`string`和一个`c风格字符串`是否相等。而两个都是`c风格字符串`的话，它们本质上是比较两个`char *`类型的指针，即所指**地址**。所以，只有当两个序列中的指针都指向相同的**地址**时，`equal` 才会返回 `true`。否则，即使字符串内容完全相同，也会返回 `false`。
###10.6
```
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
int main()
{
	vector<int> ivec(10,10);
	fill_n(ivec.begin(),ivec.size(),0);
	for(const auto &pi:ivec)
		cout<<pi<<" ";
	cout<<endl;
	return 0;
}
```
###10.7
- 
```
vector<int> vec;list<int> lst;int i;
while(cin>>i)
	lst.push_back(i);
copy(lst.cbegin(),lst.cend(),back_inserter(vec));
```
- 
```
reserve并不改变容器中元素的数量，它仅影响vector预先分配的内存空间，所以这时候的vec仍然是空的
vector<int> vec;
vec.reserve(10);
fill_n(back_inserter(vec),10,0);
```
###10.8
&emsp;标准库算法从来不 __直接__ 操作容器，它们**只**操作迭代器，从而 __间接__ 访问容器。能不能插入和删除元素，不在于算法，而在于传递给它们的**迭代器**是否具有这样的能力。
###10.9
```
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void elimDups(vector<string> &);
void pt(vector<string> &);
int main(void)
{
	string tmp;
	vector<string> svec;
	while(cin>>tmp)
		svec.push_back(tmp);
	elimDups(svec);
	return 0;
}
void elimDups(vector<string> &svec)
{
	pt(svec);
	sort(svec.begin(),svec.end());
	pt(svec);
	vector<string>::iterator end_unique=unique(svec.begin(),svec.end());
	pt(svec);
	svec.erase(end_unique,svec.end());
	pt(svec);
}
void pt(vector<string> &svec)
{
	for(const auto &s:svec)
		cout<<s<<" ";
	cout<<endl;
}
```
###10.10
&emsp;算法只操作迭代器，由迭代器真正实现对容器的访问，因此算法根本就不知道容器的存在，所以是否改变容器的大小完全是迭代器的选择与责任。
###10.11
```
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void elimDups(vector<string> &);
void pt(vector<string> &);
bool isShorter(const string &s1,const string &s2)
{
	return s1.size()<s2.size();
}
int main(void)
{
	string tmp;
	vector<string> svec;
	while(cin>>tmp)
		svec.push_back(tmp);
	elimDups(svec);
	stable_sort(svec.begin(),svec.end(),isShorter);
	pt(svec);
	return 0;
}
void elimDups(vector<string> &svec)
{
	pt(svec);
	sort(svec.begin(),svec.end());
	pt(svec);
	vector<string>::iterator end_unique=unique(svec.begin(),svec.end());
	pt(svec);
	svec.erase(end_unique,svec.end());
	pt(svec);
}
void pt(vector<string> &svec)
{
	for(const auto &s:svec)
		cout<<s<<" ";
	cout<<endl;
}
```
###10.12
```
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
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
	Sales_data():Sales_data("",0,0){}
	Sales_data(istream &is):Sales_data(){read(is,*this);}
	Sales_data(const string &s):Sales_data(s,0,0){}
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
bool compareIsbn(Sales_data &s1,Sales_data &s2)
{
	return s1.isbn()<s2.isbn();
}
int main(void)
{
	Sales_data tmp;
	vector<Sales_data> Sales_data_vec;
	while(read(cin,tmp))
		Sales_data_vec.push_back(tmp);
	sort(Sales_data_vec.begin(),Sales_data_vec.end(),compareIsbn);
	for(auto &t:Sales_data_vec)
	{
		print(cout,t);
		cout<<endl;
	}
	return 0;
}
```
###10.13
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
bool divide(const string &s)
{
	return s.size()>=5;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	while(cin>>tmp)
		svec.push_back(tmp);
	const auto p=partition(svec.begin(),svec.end(),divide);
	for(auto beg=svec.cbegin();beg!=p;++beg)
		cout<<*beg<<" ";
	cout<<endl;
	return 0;
}
```
###10.14
```
[](int a,int b)-> return int{return a+b;}
```
###10.15
```
[a](int b)-> return int {return a+b;}
```
###10.16
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
void elimDups(vector<string> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &s1,const string &s2)-> bool {return s1.size()<s2.size();});
	auto wc=find_if(words.begin(),words.end(),[sz](const string &s)-> bool {return s.size()>=sz;});
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" of length "<<sz<<" or longer "<<endl;
	for_each(wc,words.end(),[](const string &s){cout<<s<<" ";});
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,3);
	return 0;
}
```
###10.17
```
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
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
	Sales_data():Sales_data("",0,0){}
	Sales_data(istream &is):Sales_data(){read(is,*this);}
	Sales_data(const string &s):Sales_data(s,0,0){}
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
bool compareIsbn(Sales_data &s1,Sales_data &s2)
{
	return s1.isbn()<s2.isbn();
}
int main(void)
{
	Sales_data tmp;
	vector<Sales_data> Sales_data_vec;
	while(read(cin,tmp))
		Sales_data_vec.push_back(tmp);
	sort(Sales_data_vec.begin(),Sales_data_vec.end(),[](Sales_data &d1,Sales_data&d2)->bool{return d1.isbn()<d2.isbn();});
	for(auto &t:Sales_data_vec)
	{
		print(cout,t);
		cout<<endl;
	}
	return 0;
}
```
###10.18
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
void elimDups(vector<string> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &s1,const string &s2)-> bool {return s1.size()<s2.size();});
	auto wc=partition(words.begin(),words.end(),[sz](const string &s)-> bool {return s.size()<sz;});
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" of length "<<sz<<" or longer "<<endl;
	for_each(wc,words.end(),[](const string &s){cout<<s<<" ";});
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,3);
	return 0;
}
```
###10.19
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
void elimDups(vector<string> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &s1,const string &s2)-> bool {return s1.size()<s2.size();});
	auto wc=stable_partition(words.begin(),words.end(),[sz](const string &s)-> bool {return s.size()<sz;});
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" of length "<<sz<<" or longer "<<endl;
	for_each(wc,words.end(),[](const string &s){cout<<s<<" ";});
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,3);
	return 0;
}
```
###10.20
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
void elimDups(vector<string> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &s1,const string &s2)-> bool {return s1.size()<s2.size();});
	auto wc=find_if(words.begin(),words.end(),[sz](const string &s)-> bool {return s.size()>sz;});
	auto count=count_if(words.begin(),words.end(),[=](const string &s)->bool {return s.size()>sz;});
	cout<<count<<" "<<make_plural(count,"word","s")<<" longer than "<<sz<<endl;
	for_each(wc,words.end(),[](const string &s){cout<<s<<" ";});
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,6);
	return 0;
}
```
###10.21
`[i]()mutable->bool{if(i>0) {--i;return false;}else return true;};`
###10.22
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;
void elimDups(vector<string> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
bool check_sz(const string &s,string::size_type sz)
{
	return s.size()>sz;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &s1,const string &s2)-> bool {return s1.size()<s2.size();});
	auto wc=find_if(words.begin(),words.end(),bind(check_sz,_1,sz));
	auto count=wc-words.begin();
	cout<<count<<" "<<make_plural(count,"word","s")<<" short than "<<sz<<endl;
	for_each(words.begin(),wc,[](const string &s){cout<<s<<" ";});
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,6);
	return 0;
}
```
###10.23
&emsp;`bind`是**可变**参数的。它接受的第一个参数是*可调用对象*，即实际工作函数A，返回供算法调用的新的可调用对象B。若A接受X个参数，则`bind`的参数个数就是X+1个，即除了A自身外，其他参数与A的形参一一对应。这些参数中，有些是占位符（_n），另外一些来自所处函数的局部变量。
###10.24
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;
bool check_sz(const string &s,string::size_type sz)
{
	return s.size()>sz;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some string(q to quit):";
	while(cin>>tmp&&tmp!="q")
		svec.push_back(tmp);
	cout<<"Which string longer than:";
	cin>>tmp;
	auto p=find_if(svec.begin(),svec.end(),bind(check_sz,_1,tmp.size()));
	cout<<"The first longer than "<<tmp<<" is "<<*p<<endl;
	return 0;
}
```
###10.25
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;
void elimDups(vector<string> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
bool check_sz(const string &s,string::size_type sz)
{
	return s.size()<sz;
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &s1,const string &s2)-> bool {return s1.size()<s2.size();});
	auto wc=partition(words.begin(),words.end(),bind(check_sz,_1,sz));
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" of length "<<sz<<" or longer "<<endl;
	for_each(wc,words.end(),[](const string &s){cout<<s<<" ";});
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,3);
	return 0;
}
```
###10.26
&emsp;`back_inserter`创建一个使用`push_back`的迭代器，`front_inserter`创建一个使用`push_front`的迭代器，`inserter`创建一个使用`insert`的迭代器。使用`front_inserter`向容器插入一些元素，元素最终在容器中的顺序与插入顺序相反，但 `back_inserter` 和 `inserter` 则不会有这个问题。
###10.27
```
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int main(void)
{
	list<int> ilst;
	vector<int> ivec{9,1,9,2,2,3,3,3,4,4,4,4,5,5,5,5,5};
	sort(ivec.begin(),ivec.end(),[](const int a,const int b)->bool{return a<b;});
	unique_copy(ivec.begin(),ivec.end(),back_inserter(ilst));
	for_each(ilst.begin(),ilst.end(),[](const int i)->void{cout<<i<<" ";});
	return 0;
}
```
###10.28
```
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <algorithm>
using namespace std;
int main(void)
{
	forward_list<int> iflst;
	list<int> ilst;
	deque<int> idq;
	vector<int> ivec{1,2,3,4,5,6,7,8,9};
	copy(ivec.begin(),ivec.end(),front_inserter(iflst));
	copy(ivec.begin(),ivec.end(),inserter(ilst,ilst.begin()));
	copy(ivec.begin(),ivec.end(),back_inserter(idq));

	for_each(iflst.begin(),iflst.end(),[](const int i)->void{cout<<i<<" ";});
	cout<<'\n';
	for_each(ilst.begin(),ilst.end(),[](const int i)->void{cout<<i<<" ";});
	cout<<'\n';
	for_each(idq.begin(),idq.end(),[](const int i)->void{cout<<i<<" ";});
	cout<<'\n';
	return 0;
}
```
###10.29
```
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	istream_iterator<string> it(infile),eof;
	vector<string> svec(it,eof);
	for_each(svec.begin(),svec.end(),[](const string &s)->void{cout<<s<<" ";});
	cout<<endl;
	return 0;
}
```
###10.30
```
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;
int main(void)
{
	istream_iterator<int> it(cin),eof;
	ostream_iterator<int> ot(cout," ");
	vector<int> ivec(it,eof);
	sort(ivec.begin(),ivec.end());
	copy(ivec.begin(),ivec.end(),ot);
	return 0;
}
```
###10.31
```
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;
int main(void)
{
	istream_iterator<int> it(cin),eof;
	ostream_iterator<int> ot(cout," ");
	vector<int> ivec(it,eof);
	sort(ivec.begin(),ivec.end());
	unique_copy(ivec.begin(),ivec.end(),ot);
	return 0;
}
```
###10-32
```
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "Sales_item.h"
using namespace std;
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	istream_iterator<Sales_item> it(infile),eof;
	vector<Sales_item> Sales_vec(it,eof);
	sort(Sales_vec.begin(),Sales_vec.end(),compareIsbn);
	vector<Sales_item>::iterator bg=Sales_vec.begin(),ed;
	while(bg!=Sales_vec.end())
	{
		ed=find_if_not(bg,Sales_vec.end(),[bg](Sales_item &s)->bool{return s.isbn()==bg->isbn();});
		cout<<accumulate(bg,ed,Sales_item(bg->isbn()))<<endl;
		bg=ed;
	}
	return 0;
}
```
###10.33
```
#include <iostream>
#include <fstream>
#include <iterator>
using namespace std;
int main(int argc,char *argv[])//三个参数第一个是输入文件，第二个输出奇数，第三个输出偶数
{
	if(argc!=4)
	{
		cerr<<"usage: ./a.out arg1 arg2 arg3\n";
		return EXIT_FAILURE;
	}
	ifstream infile(argv[1]);
	ofstream ofile1(argv[2]),ofile2(argv[3]);
	istream_iterator<int> it(infile),eof;
	ostream_iterator<int> odd(ofile1," "),even(ofile2,"\n");
	while(it!=eof)
		if(*it%2)
			odd=*it++;
		else
			even=*it++;
	return 0;
}
```
###10.34
```
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
	vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
	for_each(ivec.crbegin(),ivec.crend(),[](int i)->void{cout<<i<<" ";});
	cout<<'\n';
	return 0;
}
```
###10.35
```
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
	vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
	for(auto p=ivec.end()-1;p!=ivec.begin()-1;--p)
		cout<<*p<<" ";
	cout<<'\n';
	return 0;
}
```
###10.36
```
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
int main(void)
{
	list<int> ilst{3,0,2,1,5,4,0,8,0,9};
	auto p=find(ilst.crbegin(),ilst.crend(),0);
	++p;
	int count=0;
	for(auto bg=ilst.begin();bg!=p.base();++bg,++count);
	cout<<"最后一个值为零的元素在list中下标为"<<count<<"的位置上。"<<endl;
	return 0;
}
```
###10.37
```
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int main(void)
{
	list<int> ilst;
	vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
	vector<int>::reverse_iterator rbg(ivec.begin()+7),red(ivec.begin()+2);
	copy(rbg,red,back_inserter(ilst));
	for_each(ilst.begin(),ilst.end(),[](int i)->void{cout<<i<<" ";});
	cout<<endl;
	return 0;
}
```
###10.38
- 输入迭代器：只读，不写；单遍扫描，只能递增；还支持相等性判定运算（==、!=）、解引用运算符（*）（只出现在赋值运算符右侧）和箭头运算符（->）。
- 输出迭代器：只写，不读；单遍扫描，只能递增；支持解引用运算符（*）（只出现在赋值运算符左侧）。
- 前向迭代器：可读、写；多遍扫描；只能递增；支持所有输入、输出迭代器的操作。
- 双向迭代器：可读、写；多遍扫描；可递增、递减；支持所有向前迭代器操作。
- 随机访问迭代器：可读、写；多遍扫描；支持全部迭代器运算，除了上述迭代器类别支持的操作外，还有：
	1. 比较两个迭代器相对位置的关系运算符（<、<=、> 和 >=）
	2. 迭代器和一个整数值的加减运算（+、+=、- 和 -=）令迭代器在序列中前进或后退给定整数个元素
	3. 两个迭代器上的减法运算符（-）得到其距离
	4. 下标运算符
###10.39
&emsp;`list`上的迭代器属于双向迭代器，`vector`上的迭代器属于随机访问迭代器。
###10.40
&emsp;`copy`的前两个参数要求输入迭代器，第三个参数要求输出迭代器。`reverse`的两个参数要求双向迭代器。`unique`要求两个参数是前向迭代器。
###10.41
- replace(beg,end,old_val,new_val)将beg至end范围内的old_val替换为new_val
- replace_if(beg,end,pred,new_val)将beg至end范围内谓词返回true的元素替换为new_val
- replace_copy(beg,end,dest,old_val,new_val)将beg至end范围内的old_val替换为new_val，并将新的元素序列写入dest
- replace_copy_if(beg,end,dest,pred,new_val)将beg至end范围内谓词返回true的元素替换为new_val,并将新的元素序列写入dest
###10.42
```
#include <iostream>
#include <list>
using namespace std;
void elimDups(list<string> &);
void pt(list<string> &);
int main(void)
{
	string tmp;
	list<string> slst;
	while(cin>>tmp)
		slst.push_back(tmp);
	elimDups(slst);
	return 0;
}
void elimDups(list<string> &slst)
{
	pt(slst);
	slst.sort();
	pt(slst);
	slst.unique();
	pt(slst);
}
void pt(list<string> &slst)
{
	for(const auto &s:slst)
		cout<<s<<" ";
	cout<<endl;
}
```
