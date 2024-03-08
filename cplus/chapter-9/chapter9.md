[toc]

### 9.1
1. 相对来说list更好，任何位置的插入/删除操作更快
2. deque头尾插入/删除更快
3. 排序的话支持随机访问更快，故vector或deque更好
### 9.2
`list<deque<int>> ld;`
### 9.3
指向同一个容器中的元素或尾元素之后的位置，可以反复递增begin来到达end。
### 9.4
```
#include <vector>
bool find_target(vector<int>::const_iterator beg,vector<int>::const_iterator ed,int val)
{
	while(beg!=ed)
	{
		if(*beg==val)
			return true;
		++beg;
	}
	return false;
}
```
### 9.5
```
#include <vector>
vector<int>::iterator find_target(vector<int>::iterator beg,vector<int>::iterator ed,int val)
{
	while(beg!=ed)
	{
		if(*beg==val)
			return beg;
		++beg;
	}
	return beg;
}
```
### 9.6
list的迭代器不支持小于运算符
```
list<int> lst1;
list<int>::iterator iter1=lst1.begin(),iter2=lst1.end();
while(iter1!=iter2) /*......*/
```
### 9.7
`vector<int>::iterator`
### 9.8
`list<string>::value_type`
`list<string>::reference`
### 9.9
begin函数被重载过，常量对象调用会返回常量迭代器，普通对象调用会返回普通迭代器。而cbegin则都返回常量迭代器。
### 9.10
it1是普通迭代器，it2、it3、it4都是常量迭代器。
### 9.11
```
vector<int> ivec1;//一个空的元素类型为int的vector
vector<int> ivec2(ivec1);//ivec2初始化为ivec1的拷贝，包含ivec1中所有元素的副本
vector<int> ivec3=ivec1;//同上
vector<int> ivec4{1,2,3,4};//列表初始化，ivec4中包含列表中所有元素的拷贝
vector<int> ivec5={1,2,3,4};//同上
vector<int> ivec6(4);//ivec6中包含4个执行值初始化的元素
vector<int> ivec7(4,4);//ivec7中包含4个值为4的元素
vector<int> ivec8(ivec1.begin(),ivec1.end());//ivec8初始化为迭代器ivec1.begin()和ivec1.end()指定的范围中的元素，不含ivec.end()所指的元素
```
### 9.12
接受一个容器创建其拷贝的构造函数，容器类型和元素类型都必须相同，实现完整拷贝。而接受两个迭代器创建拷贝的构造函数，容器类型则不必相同，元素类型可转换即可，可以拷贝指定的元素范围。
### 9.13
```
#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	list<int> il{1,2,3,4,5};
	vector<int> ivec{2,3,4,5,6};
	vector<double> dvec1(il.begin(),il.end());//因为容器类型不同，且元素类型不同，只能使用迭代器指定的范围初始化
	vector<double> dvec2(ivec.begin(),ivec.end());//因为元素类型不同，只能使用迭代器指定的范围初始化
	for(const auto &a:dvec1)
		cout<<a<<" ";
	cout<<endl;
	for(const auto &b:dvec2)
		cout<<b<<" ";
	cout<<endl;
	return 0;
}
```
### 9.14
```
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;
int main(void)
{
	list<const char *> clist={"wo","shi","shei"};
	vector<string> svec;
	svec.assign(clist.cbegin(),clist.cend());
	for(const auto &a:svec)
		cout<<a<<" ";
	cout<<endl;
	return 0;
}
```
### 9.15
```
#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
	vector<int> iv1={1,2,3},iv2{1,2,3};
	if(iv1==iv2)
		cout<<"It's equal.";
	else
		cout<<"Not equal.";
	cout<<endl;
	return 0;
}
```
### 9.16
```
#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	list<int> il={1,2,3};
	vector<int> iv{1,2,3};
	for(auto pl=il.cbegin();pl!=il.cend();pl++)
		for(auto pv=iv.cbegin();pv!=iv.cend();pv++)
		{
			if(*pl==*pv)
				cout<<*pl<<" equal "<<*pv<<endl;
			else
				cout<<*pl<<" is not equal "<<*pv<<endl;
		}
	return 0;
}
```
### 9.17
c1和c2必须是相同类型的容器，保存相同类型的元素，元素类型必须支持所需的运算符。
### 9.18
```
#include <iostream>
#include <string>
#include <deque>
using namespace std;
int main(void)
{
	deque<string> sd;
	string str;
	while(cin>>str)
		sd.push_front(str);
	for(auto psd=sd.cbegin();psd!=sd.cend();++psd)
		cout<<*psd<<endl;
	return 0;
}
```
### 9.19
```
#include <iostream>
#include <string>
#include <list>
using namespace std;
int main(void)
{
	list<string> sl;
	string str;
	while(cin>>str)
		sl.push_front(str);
	for(auto psl=sl.cbegin();psl!=sl.cend();++psl)
		cout<<*psl<<endl;
	return 0;
}
```
### 9.20
```
#include <iostream>
#include <list>
#include <deque>
using namespace std;
int main(void)
{
	list<int> il;
	deque<int> oddq,evenq;
	int tmp;
	while(cin>>tmp)
		il.push_back(tmp);
	for(auto pl=il.cbegin();pl!=il.cend();++pl)
	{
		if(*pl%2==0)
			evenq.push_back(*pl);
		else
			oddq.push_back(*pl);
	}
	cout<<"The odd numbers: ";
	for(auto pd1=oddq.cbegin();pd1!=oddq.cend();++pd1)
		cout<<*pd1<<" ";
	cout<<endl;
	cout<<"The even numbers: ";
	for(auto pd2=evenq.cbegin();pd2!=evenq.cend();++pd2)
		cout<<*pd2<<" ";
	cout<<endl;
	return 0;
}
```
### 9.21
即可在vector实现push_front的功能，但性能会大幅降低。
### 9.22
主要错误在于：
1. 向一个 vector、string 或 deque 插入元素会使现有指向容器的迭代器、引用和指针失效
2. 循环体内未对判断条件做出修改，可能导致死循环
```cpp
vector<int>::iterator iter=iv.begin(),mid=iv.begin()+iv.size()/2;
while(iter!=mid)
{
    if(*iter==some_val)
    {
        iter=iv.insert(iter,2*some_val);//插入新元素后，会返回指向新元素的迭代器
        iter+=2;//加上插入的新元素，需前进两位
        mid=iv.begin()+iv.size()/2;//重新计算mid
    }
    else
        ++iter;
}
```
### 9.23
都等于容器中唯一元素的值。
### 9.24
```
#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
	vector<int> ivec;
	cout<<ivec[0]<<endl;
	cout<<ivec.at(0)<<endl;
	cout<<ivec.front()<<endl;
	cout<<*ivec.begin()<<endl;
	return 0;
}
```
### 9.25
如果elem1和elem2相等，或者皆为尾后迭代器，则不会发生任何操作。如果elem1是除尾后迭代器之外的任何迭代器，则会删除容器中含elem1所指元素及之后的所有元素。
### 9.26
```
#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	vector<int> ivec;
	list<int> il;
	int ia[]={0,1,1,2,3,5,8,13,21,55,89};
	for(int index=0;index<(sizeof(ia)/sizeof(*ia));index++)
	{
		ivec.push_back(ia[index]);
		il.push_back(ia[index]);
	}
	for(auto pvec=ivec.begin();pvec!=ivec.end();)
	{
		if(*pvec%2==0)
			pvec=ivec.erase(pvec);
		else
			++pvec;
	}
	for(auto plist=il.begin();plist!=il.end();)
	{
		if(*plist%2)
			plist=il.erase(plist);
		else
			++plist;
	}
	cout<<"in the vector: ";
	for(const auto &vec:ivec)
		cout<<vec<<" ";
	cout<<endl;
	cout<<"in the list: ";
	for(const auto &lst:il)
		cout<<lst<<" ";
	cout<<endl;
	return 0;
}
```
### 9.27
```
#include <iostream>
#include <forward_list>
using namespace std;
int main(void)
{
	forward_list<int> ifl{0,1,2,3,4,5,6,7,8,9};
	for(auto prev=ifl.before_begin(),curr=ifl.begin();curr!=ifl.end();)
	{
		if(*curr%2)
			curr=ifl.erase_after(prev);
		else
			prev=curr++;
	}
	for(const auto &p:ifl)
		cout<<p<<" ";
	cout<<endl;
	return 0;
}
```
### 9.28
```
#include <iostream>
#include <forward_list>
using namespace std;
void test_and_insert(forward_list<string> &sflst, const string &s1, const string &s2) {
    auto prev = sflst.before_begin();               // 前驱元素
    auto curr = sflst.begin();                      // 当前元素
    bool inserted = false;
    while (curr != sflst.end()) {
        if (*curr == s1) {                          // 找到给定字符串
            curr = sflst.insert_after(curr, s2);    // 插入新字符串，curr 指向它
            inserted = true;
            return;
        } else {
            prev = curr;                            // 前驱和当前迭代器都向前推进
            ++curr;
        }
    }
    if (!inserted)
        sflst.insert_after(prev, s2);               // 未找到给定字符串，插入尾后
}
int main() {
    forward_list<string> sflst = {"Hello", "!", "world", "!"};
    test_and_insert(sflst, "Hello", "你好");
    for (auto curr = sflst.cbegin(); curr != sflst.cend(); ++curr)
        cout << *curr << " ";
    cout << endl;
    test_and_insert(sflst, "!", "?");
    for (auto curr = sflst.cbegin(); curr != sflst.cend(); ++curr)
        cout << *curr << " ";
    cout << endl;
    test_and_insert(sflst, "Bye", "再见");
    for (auto curr = sflst.cbegin(); curr != sflst.cend(); ++curr)
        cout << *curr << " ";
    cout << endl;
    return 0;
}
```
### 9.29
`vec.resize(100)`会将75个值初始化的新元素添加到`vec`尾部。
`vec.resize(10)`又会从`vec`末尾删除90个元素。
### 9.30
如果元素是类类型的话，元素类型必须提供一个默认构造函数。
### 9.31
对于list及forward_list插入、删除操作并未影响迭代器的有效性，同时迭代器不支持加减运算，只能使用自增。另外对于forward_list，因为有特殊的插入删除操作，所以需额外维护一个前驱迭代器。
```cpp
#include <iostream>
#include <list>
using namespace std;
int main(void)
{
	list<int> il={0,1,2,3,4,5,6,7,8,9};
	auto bg=il.begin(),ed=il.end();
	while(bg!=ed)
	{
		if(*bg%2)
		{
			il.insert(bg,*bg);
			++bg;
		}
		else
			bg=il.erase(bg);
	}
	for(const auto &i:il)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
```
```cpp
#include <iostream>
#include <forward_list>
using namespace std;
int main(void)
{
	forward_list<int> ifl={0,1,2,3,4,5,6,7,8,9};
	auto prev=ifl.before_begin(),cur=ifl.begin(),ed=ifl.end();
	while(cur!=ed)
	{
		if(*cur%2)
		{
			ifl.insert_after(prev,*cur);
			prev=cur;
			++cur;
		}
		else
			cur=ifl.erase_after(prev);
	}
	for(const auto &i:ifl)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
```
### 9.32
不合法，实参的求值顺序依赖编译器，若先自增，则程序不合本意。
### 9.33
因为此时begin已失效，程序出现错误。
### 9.34
死循环，insert返回插入后元素的迭代器，所指元素依然是奇数，且iter永远不会前进到vi.end()。
修改时，应该将循环部分用花括号括起来，并且iter自增两次。
### 9.35
capacity不分配新的内存空间的情况下可以保存的最多的元素，size当前实际保存的元素数量。
### 9.36
不可能，相等后会在下一次增长的操作时分配新的空间。
### 9.37
list不需要，因为一个链表占用的内存空间总是与它当前保存的的元素所需的空间相等。而array是固定大小的数组，内存一次性分配。
### 9.38
```
#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
	vector<int> ivec;
	cout<<"ivec: size: "<<ivec.size()<<" capacity: "<<ivec.capacity()<<endl;
	for(vector<int>::size_type ix=0;ix!=24;++ix)
		ivec.push_back(ix);
	cout<<"ivec: size: "<<ivec.size()<<" capacity: "<<ivec.capacity()<<endl;
	ivec.reserve(50);
	cout<<"ivec: size: "<<ivec.size()<<" capacity: "<<ivec.capacity()<<endl;
	while(ivec.size()!=ivec.capacity())
		ivec.push_back(0);
	cout<<"ivec: size: "<<ivec.size()<<" capacity: "<<ivec.capacity()<<endl;
	ivec.push_back(42);
	cout<<"ivec: size: "<<ivec.size()<<" capacity: "<<ivec.capacity()<<endl;
	ivec.shrink_to_fit();
	cout<<"ivec: size: "<<ivec.size()<<" capacity: "<<ivec.capacity()<<endl;
	return 0;
}
```
### 9.39
```
vector<string> svec;
svec.reserve(1024);//分配至少能容纳1024个string的内存空间
string word;
while(cin>>word)
	svec.push_back(word);//从标准输入中读取元素，若读取数目超过1024，则会重新分配更大的内存空间
svec.resize(svec.size()+svec.size()/2);//调整svec的大小为当前元素数目的1.5倍，新添加的元素初始化为空的string，若调整后的数目超过当前的capacity则会重新分配更大的内存空间
```
### 9.40
```
#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
	vector<string> svec;
	svec.reserve(1024);//分配至少能容纳1024个string的内存空间
	cout<<"svec: size: "<<svec.size()<<" capacity: "<<svec.capacity()<<endl;
	string word;
	string::size_type count;
	cout<<"numbers: ";
	cin>>count;
	while(svec.size()!=count)
		svec.push_back(" ");//从标准输入中读取元素，若读取数目超过1024，则会重新分配更大的内存空间
	cout<<"svec: size: "<<svec.size()<<" capacity: "<<svec.capacity()<<endl;
	svec.resize(svec.size()+svec.size()/2);//调整svec的大小为当前元素数目的1.5倍，新添加的元素初始化为空的string，若调整后的数目超过当前的capacity则会重新分配更大的内存空间
	cout<<"svec: size: "<<svec.size()<<" capacity: "<<svec.capacity()<<endl;
	return 0;
}
```
### 9.41
```
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(void)
{
	vector<char> cvec{'H','e','l','l','o',' ','W','o','r','l','d'};
	string s(cvec.data(),cvec.size());
	cout<<s<<endl;
	return 0;
}
```
### 9.42
可以利用reserve先分配内存，再逐个的push_back。
### 9.43
```
#include <iostream>
#include <string>
using namespace std;
void rep(string &s,const string &oldVal,const string &newVal)
{
	for(auto beg=s.begin();oldVal.size()<=(s.end()-beg);)
	{
		if(string{beg,beg+oldVal.size()}==oldVal)
		{
			beg=s.erase(beg,beg+oldVal.size());
			beg=s.insert(beg,newVal.begin(),newVal.end());
			advance(beg,newVal.size());
		}
		else
			++beg;
	}
}
int main(void)
{
	string s={"I tho  thru do it!"};
	rep(s,"tho","though");
	cout<<s<<endl;
	rep(s,"thru","through");
	cout<<s<<endl;
	return 0;
}
```
### 9.44
```
#include <iostream>
#include <string>
using namespace std;
void rep(string &s,const string &oldVal,const string &newVal)
{
	for(auto beg=s.begin();oldVal.size()<=(s.end()-beg);)
	{
		if(string{beg,beg+oldVal.size()}==oldVal)
		{
			beg=s.erase(beg,beg+oldVal.size());
			beg=s.insert(beg,newVal.begin(),newVal.end());
			advance(beg,newVal.size());
		}
		else
			++beg;
	}
}
int main(void)
{
	string s={"I tho  thru do it!"};
	rep(s,"tho","though");
	cout<<s<<endl;
	rep(s,"thru","through");
	cout<<s<<endl;
	return 0;
}
```
### 9.45
```
#include <iostream>
#include <string>
using namespace std;
string & name(string &s,const string &s1,const string &s2)
{
	s.insert(s.begin(),1,' ');
	s.insert(s.begin(),s1.begin(),s1.end());
	s.append(" "+s2);
	return s;
}
int main(void)
{
	string s,s1,s2;
	cin>>s>>s1>>s2;
	name(s,s1,s2);
	cout<<s<<endl;
	return 0;
}
```
### 9.46
```
#include <iostream>
#include <string>
using namespace std;
string & name(string &s,const string &s1,const string &s2)
{
	s.insert(0,s1+" ");
	s.insert(s.size()," "+s2);
	return s;
}
int main(void)
{
	string s,s1,s2;
	cin>>s>>s1>>s2;
	name(s,s1,s2);
	cout<<s<<endl;
	return 0;
}
```
### 9.47
==9-47-1.cpp==
```
#include <iostream>
#include <string>
using namespace std;
int main(void)
{
	string s={"ab2c3d7R4E6"};
	string numbers="0123456789",alphabets="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	cout<<"The numbers: ";
	for(string::size_type pos=0;(pos=s.find_first_of(numbers,pos))!=string::npos;++pos)
		cout<<s[pos]<<" ";
	cout<<endl;
	cout<<"The alphabets: ";
	for(string::size_type pos=0;(pos=s.find_first_of(alphabets,pos))!=string::npos;++pos)
		cout<<s[pos]<<" ";
	cout<<endl;
	return 0;
}
```
==9-47-2.cpp==
```
#include <iostream>
#include <string>
using namespace std;
int main(void)
{
	string s={"ab2c3d7R4E6"};
	string numbers="0123456789",alphabets="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	cout<<"The numbers: ";
	for(string::size_type pos=0;(pos=s.find_first_not_of(alphabets,pos))!=string::npos;++pos)
		cout<<s[pos]<<" ";
	cout<<endl;
	cout<<"The alphabets: ";
	for(string::size_type pos=0;(pos=s.find_first_not_of(numbers,pos))!=string::npos;++pos)
		cout<<s[pos]<<" ";
	cout<<endl;
	return 0;
}
```
### 9.48
返回string::npos
### 9.49
```
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool suit(const string &s)
{
	string target{"bdfghijklpqty"};
	if(s.find_first_of(target)==string::npos)
		return true;
	else
		return false;
}
int main(int argc,char *argv[])
{
	string word,result;
	if(argc!=2)
	{
		cerr<<"程序+文件名"<<endl;
		return EXIT_FAILURE;
	}
	ifstream fs(argv[1]);
	if(fs)
	{
		while(fs>>word)
		{
			if(suit(word))
			{
				if(word.size()>result.size())
				{
					result=word;
				}
			}
		}
	}
	if(result.size()!=0)
		cout<<"the longest word is: "<<result<<" length: "<<result.size()<<endl;
	else
		cout<<"no word suit"<<endl;
	return 0;
}
```
### 9.50
==9-50-1.cpp==
```
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	vector<string> svec;
	string tmp;
	int sum=0;
	cout<<"Enter some integer:";
	while(cin>>tmp)
	{
		svec.push_back(tmp);
	}
	for(auto &s:svec)
	{
		sum+=stoi(s);
	}
	cout<<"sum is "<<sum<<endl;
	return 0;
}
```
==9-50-2.cpp==
```
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	vector<string> svec;
	string tmp;
	double sum=0;
	cout<<"Enter some float:";
	while(cin>>tmp)
	{
		svec.push_back(tmp);
	}
	for(auto &s:svec)
	{
		sum+=stod(s);
	}
	cout<<"sum is "<<sum<<endl;
	return 0;
}
```
### 9.51
```
#include <iostream>
#include <string>
#include <array>
using namespace std;
class date
{
	public:
		date()=default;
		date(const std::string &s);
		void print() const;
	private:
		unsigned year=2023;
		unsigned month=4;
		unsigned day=2;
		array<string,12> months={"Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
		unsigned MonthFromStr(const string &s);
};
date::date(const std::string &s)
{
	string delimiter{" ,/"};
	string::size_type month_day_delimit_pos=s.find_first_of(delimiter);
	month=MonthFromStr(s.substr(0,month_day_delimit_pos));
	string::size_type day_year_delimit_pos=s.find_first_of(delimiter,month_day_delimit_pos+1);
	day=stoi(s.substr(month_day_delimit_pos+1,day_year_delimit_pos));
	year=stoi(s.substr(day_year_delimit_pos+1));
}
void date::print() const
{
	cout<<year<<" "<<month<<" "<<day<<endl;
}
unsigned date::MonthFromStr(const string &s)
{
	if(s.empty())
		return 0;
	if(isdigit(s[0]))
		return stoi(s);
	for(size_t i=0;i!=12;++i)
	{
		if(s.find(months[i])!=string::npos)
			return i+1;
	}
	return 0;
}
int main(void)
{
	date d;
	d.print();
	date e{"January 1,1900"};
	e.print();
	date f{"1/1/1990"};
	f.print();
	date g{"Jan 1 1900"};
	g.print();
	return 0;
}
```
### 9.52
```
#include <iostream>
#include <string>
#include <stack>
using namespace std;
//如果处理的是算式的话，还得考虑计算符号的优先级，比较麻烦，这里就简单的处理为将一对括号内的字符替换为*
int main(void)
{
	string examp="This is (Mooophy(awesome)((((wooooooooo))))) and (ocxs) over";
	char replace='*';
	unsigned left_bracket_count=0;
	stack<char> cstk;
	for(string::const_iterator ps=examp.cbegin();ps!=examp.cend();++ps)
	{
		cstk.push(*ps);
		if(*ps=='(')
			++left_bracket_count;
		if(*ps==')'&&left_bracket_count)
		{
			while(cstk.top()!='(')
				cstk.pop();
			cstk.pop();
			cstk.push(replace);
			--left_bracket_count;
		}
	}
	examp.clear();
	while(!cstk.empty())
	{
		examp.insert(examp.begin(),cstk.top());
		cstk.pop();
	}
	cout<<examp<<endl;
	return 0;
}
```
