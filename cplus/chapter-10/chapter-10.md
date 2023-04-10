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
accumulate的第三个参数是和的初值，它还决定了函数的返回类型以及函数中使用哪个加法运算符，所以本题中和的初始是整型，则会发生双精度浮点数向整型的转换，损失小数点后的部分。
###10.5
equal使用\==运算符比较两个序列中的元素。string类重载了\==运算符，可以比较两个string或者一个string和一个c风格字符串是否相等。而两个都是c风格字符串的话，它们本质上是比较两个char *类型的指针，即所指地址。所以，只有当两个序列中的指针都指向相同的地址时，equal 才会返回 true。否则，即使字符串内容完全相同，也会返回 false。
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
标准库算法从来不直接操作容器，它们只操作迭代器，从而间接访问容器。能不能插入和删除元素，不在于算法，而在于传递给它们的迭代器是否具有这样的能力
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
算法只操作迭代器，由迭代器真正实现对容器的访问，因此算法根本就不知道容器的存在，所以是否改变容器的大小完全是迭代器的选择与责任。
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
