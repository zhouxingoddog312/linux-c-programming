[toc]

### 8.1
<a id="1">8-1and8-2.cpp</a>
```
#include <iostream>
using namespace std;
istream &test(istream &is)
{
	string st;
A:	while(is.good())
	{
		is>>st;
		cout<<st<<'\n';
	}
	if(is.bad())
		cout<<"fatal error!"<<endl;
	else if(is.eof())
		cout<<"End of file."<<endl;
	else if(is.fail())
		goto A;
	is.clear();
	return is;
}
int main()
{
	test(cin);
	return 0;
}
```
### 8.2
[见8.1](#1)
### 8.3
&emsp;&emsp;情况很多，比如`cin`流崩溃，IO操作失败或者遇到文件结束符等。
### 8.4
```
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
void rf(const string &str)
{
	vector<string> vs;
	string stemp;
	ifstream ifst(str);
	if(ifst)
	{
		while(getline(ifst,stemp))
			vs.push_back(stemp);
		for(auto p:vs)
			cout<<p<<"#";
		cout<<endl;
	}
	else
		cout<<"open file failed."<<'\n';
}
int main(void)
{
	rf("text");
	return 0;
}
```
### 8.5
```
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
void rf(const string &str)
{
	vector<string> vs;
	string stemp;
	ifstream ifst(str);
	if(ifst)
	{
		while(ifst>>stemp)
			vs.push_back(stemp);
		for(auto p:vs)
			cout<<p<<"#";
		cout<<endl;
	}
	else
		cout<<"open file failed."<<'\n';
}
int main(void)
{
	rf("text");
	return 0;
}
```
### 8.6
```
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Sales_data
{
	string bookNo;
	unsigned units_sold{0};
	double revenue{0.0};
};
int main(int argc,char *argv[])
{
	struct Sales_data  total,trans;
	double price;
	ifstream ifst(argv[1]);

	if(ifst>>total.bookNo)
	{
		ifst>>total.units_sold>>price;
		total.revenue=total.units_sold*price;
		while(ifst>>trans.bookNo)
		{
			ifst>>trans.units_sold>>price;
			trans.revenue=trans.units_sold*price;
			if(total.bookNo==trans.bookNo)
			{
				total.units_sold+=trans.units_sold;
				total.revenue+=trans.revenue;
			}
			else
			{
				cout<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
				total.bookNo=trans.bookNo;
				total.units_sold=trans.units_sold;
				total.revenue=trans.revenue;
			}
		}
		cout<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
	}
	else
	{
		cerr<<"No data?"<<endl;
		return -1;
	}
	return 0;
}
```
### 8.7
```
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Sales_data
{
	string bookNo;
	unsigned units_sold{0};
	double revenue{0.0};
};
int main(int argc,char *argv[])
{
	struct Sales_data  total,trans;
	double price;
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);

	if(ifst>>total.bookNo)
	{
		ifst>>total.units_sold>>price;
		total.revenue=total.units_sold*price;
		while(ifst>>trans.bookNo)
		{
			ifst>>trans.units_sold>>price;
			trans.revenue=trans.units_sold*price;
			if(total.bookNo==trans.bookNo)
			{
				total.units_sold+=trans.units_sold;
				total.revenue+=trans.revenue;
			}
			else
			{
				ofst<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
				total.bookNo=trans.bookNo;
				total.units_sold=trans.units_sold;
				total.revenue=trans.revenue;
			}
		}
		ofst<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
	}
	else
	{
		cerr<<"No data?"<<endl;
		return -1;
	}
	return 0;
}
```
### 8.8
```
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Sales_data
{
	string bookNo;
	unsigned units_sold{0};
	double revenue{0.0};
};
int main(int argc,char *argv[])
{
	struct Sales_data  total,trans;
	double price;
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2],ofstream::app|ofstream::out);

	if(ifst>>total.bookNo)
	{
		ifst>>total.units_sold>>price;
		total.revenue=total.units_sold*price;
		while(ifst>>trans.bookNo)
		{
			ifst>>trans.units_sold>>price;
			trans.revenue=trans.units_sold*price;
			if(total.bookNo==trans.bookNo)
			{
				total.units_sold+=trans.units_sold;
				total.revenue+=trans.revenue;
			}
			else
			{
				ofst<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
				total.bookNo=trans.bookNo;
				total.units_sold=trans.units_sold;
				total.revenue=trans.revenue;
			}
		}
		ofst<<total.bookNo<<" "<<total.units_sold<<" "<<total.revenue<<" "<<total.revenue/total.units_sold<<endl;
	}
	else
	{
		cerr<<"No data?"<<endl;
		return -1;
	}
	return 0;
}
```
### 8.9
```
#include <sstream>
#include <iostream>
using namespace std;
istream &test(istream &is)
{
	string st;
A:	while(is.good())
	{
		is>>st;
		cout<<st<<'\n';
	}
	if(is.bad())
		cout<<"fatal error!"<<endl;
	else if(is.eof())
		cout<<"End of file."<<endl;
	else if(is.fail())
		goto A;
	is.clear();
	return is;
}
int main(void)
{
	istringstream istm("wo shi shei");
	test(istm);
	return 0;
}
```
### 8.10
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
int main(int argc,char *argv[])
{
	string tmp;
	vector<string> svec;
	ifstream ifst(argv[1]);
	while(getline(ifst,tmp))
		svec.push_back(tmp);
	for(auto element:svec)
	{
		istringstream isstm(element);
		while(isstm>>tmp)
			cout<<tmp<<endl;
	}
	return 0;
}
```
### 8.11
```
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
struct PersonInfo
{
	string name;
	vector<string> phones;
};
int main(void)
{
	string line,word;
	vector<PersonInfo> people;
	istringstream record;
	while(getline(cin,line))
	{
		PersonInfo info;
		record.clear(record.rdstate()&~record.failbit&~record.eofbit);
		record.str(line);
		record>>info.name;
		while(record>>word)
			info.phones.push_back(word);
		people.push_back(info);
	}
	for(auto pi:people)
	{
		cout<<pi.name<<endl;
		for(auto ph:pi.phones)
			cout<<ph<<" ";
		cout<<endl;
	}
	return 0;
}
```
### 8.12
&emsp;&emsp;因为每个人的电话条目数量不同，所以应该缺省初始化后在程序中设置人名，并逐个添加电话。
### 8.13
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
bool valid(const string &str);
string format(const string &str);
struct PersonInfo
{
	string name;
	vector<string> phones;
};
int main(int argc,char *argv[])
{
	string line,word;
	vector<PersonInfo> people;
	istringstream record;
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);
	while(getline(ifst,line))
	{
		PersonInfo info;
		record.clear(record.rdstate()&~record.failbit&~record.eofbit);
		record.str(line);
		record>>info.name;
		while(record>>word)
			info.phones.push_back(word);
		people.push_back(info);
	}
	for(const auto &pi:people)
	{
		ostringstream formatted,badnums;
		for(const auto &ph:pi.phones)
		{
			if(!valid(ph))
				badnums<<" "<<ph;
			else
				formatted<<" "<<format(ph);
		}
		if(badnums.str().empty())
			ofst<<pi.name<<" "<<formatted.str()<<endl;
		else
			cerr<<"input error: "<<pi.name<<" invalid numbers "<<badnums.str()<<endl;
	}
	return 0;
}
bool valid(const string &str)
{
	if(str.size()==11)
		return true;
	else
		return false;
}
string format(const string &str)
{
	return str;
}
```
### 8.14
&emsp;&emsp;`const`表明循环中不会改变这些项的值，`auto`利用编译器推断`entry`和`nums`的类型，简化代码，`&`表示引用可以避免拷贝。
