[toc]
### 5.1
单独的分号就是一条空语句，在语法上需要一条语句而逻辑上不需要时，会用到空语句。
### 5.2
用花括号括起来的语句和声明序列等就是块，在语法上需要一条语句而逻辑上需要多条语句时，就会用到块。
### 5.3
```
#include <iostream>
using namespace std;
int main()
{
	int sum=0,val=1;
	while(val<=10)
		sum+=val,++val;
	cout<<"Sum of 1 to 10 inclusive is "<<sum<<endl;
	return 0;
}
```
代码的可读性降低了。
### 5.4
1. `iter=s.begin();while(string::iterator iter!=s.end()){/*......*/}`原文中，iter未初始化。
2. `while(bool status=find(word)) {/*......*/}`
`if(!status){/*......*/}`
`status`是`while`部分的局部变量，离开`while`语句，在`if`语句中已超出其作用域，所以其在`if`语句中是一个无效变量。
### 5.5
```
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	vector<string> svec{"F","D","C","B","A","A++"};
	unsigned grade=0;
	string gradelevel;
	while(cin>>grade&&grade<=100)
	{
		if(grade<60)
			gradelevel=svec[0];
		else
			gradelevel=svec[(grade-50)/10];
		if(grade!=100)
		{
			if(grade%10>7)
				gradelevel+="+";
			else if(grade%10<4)
				gradelevel+="-";
		}
		cout<<"grade is "<<gradelevel<<endl;
	}
	return 0;
}
```
### 5.6
```
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	vector<string> svec{"F","D","C","B","A","A++"};
	unsigned grade=0;
	string gradelevel;
	while(cin>>grade&&grade<=100)
	{
		gradelevel=grade<60?svec[0]:grade<70?svec[1]:grade<80?svec[2]:grade<90?svec[3]:grade<100?svec[4]:svec[5];
		gradelevel+=grade==100?"":grade%10>7?"+":grade%10<4?"-":"";
		cout<<"grade is "<<gradelevel<<endl;
	}
	return 0;
}
```
### 5.7
1. 
```
if(ival1!=ival2)
    ival1=ival2;
else
    ival1=ival2=0;
```
2.
```
if(ival<minval)
{
    minval=ival;
    occurs=1;
}
```
3.
```
if(int ival=get_value())
{
    cout<<"ival="<<ival<<endl;
    if(!ival)
        cout<<"ival=0\n";
}
```
4.
```
if(ival==0)
    ival=get_value();
```
### 5.8
悬垂else描述的是，当if分支多于else分支时，else和哪个if匹配的问题。C++语言规定其与离它最近的尚未匹配的if匹配。
### 5.9
```
#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
	int cnt=0;
	char ch;
	while((ch=getchar())!=EOF)
	{
		if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u')
			cnt++;
	}
	cout<<"cnt= "<<cnt<<"\n";
	return 0;
}
```
### 5.10
```
#include <iostream>
using namespace std;
int main()
{
	int acnt=0,ecnt=0,icnt=0,ocnt=0,ucnt=0;
	char ch;
	while(cin>>ch)
	{
		switch(ch)
		{
			case 'a':case'A':
				acnt++;
				break;
			case 'e':case 'E':
				ecnt++;
				break;
			case 'i':case 'I':
				icnt++;
				break;
			case 'o':case 'O':
				ocnt++;
				break;
			case 'u':case 'U':
				ucnt++;
				break;
			default:
				;
		}
	}
	cout<<"Number of vowel a:\t"<<acnt<<endl;
	cout<<"Number of vowel e:\t"<<ecnt<<endl;
	cout<<"Number of vowel i:\t"<<icnt<<endl;
	cout<<"Number of vowel o:\t"<<ocnt<<endl;
	cout<<"Number of vowel u:\t"<<ucnt<<endl;
	return 0;
}
```
### 5.11
```
#include <iostream>
using namespace std;
int main()
{
	int acnt=0,ecnt=0,icnt=0,ocnt=0,ucnt=0,spacecnt=0,tcnt=0,ncnt=0;
	char ch;
	while(cin.get(ch))
	{
		switch(ch)
		{
			case 'a':case'A':
				acnt++;
				break;
			case 'e':case 'E':
				ecnt++;
				break;
			case 'i':case 'I':
				icnt++;
				break;
			case 'o':case 'O':
				ocnt++;
				break;
			case 'u':case 'U':
				ucnt++;
				break;
			case ' ':
				spacecnt++;
				break;
			case '\t':
				tcnt++;
				break;
			case '\n':
				ncnt++;
				break;
			default:
				;
		}
	}
	cout<<"Number of vowel a:\t"<<acnt<<endl;
	cout<<"Number of vowel e:\t"<<ecnt<<endl;
	cout<<"Number of vowel i:\t"<<icnt<<endl;
	cout<<"Number of vowel o:\t"<<ocnt<<endl;
	cout<<"Number of vowel u:\t"<<ucnt<<endl;
	cout<<"Number of vowel space:\t"<<spacecnt<<endl;
	cout<<"Number of vowel \\t:\t"<<tcnt<<endl;
	cout<<"Number of vowel \\n:\t"<<ncnt<<endl;
	return 0;
}
```
### 5.12
```
#include <iostream>
using namespace std;
int main()
{
	int ffcnt=0,flcnt=0,ficnt=0;
	char ch1,ch2;
	cin>>ch1;
	while(cin>>ch2)
	{
		if(ch1=='f')
		{
			switch(ch2)
			{
				case 'f':
					ffcnt++;
					break;
				case 'l':
					flcnt++;
					break;
				case 'i':
					ficnt++;
					break;
			}
		}
		ch1=ch2;
	}
	cout<<"Number of ff:\t"<<ffcnt<<endl;
	cout<<"Number of fl:\t"<<flcnt<<endl;
	cout<<"Number of fi:\t"<<ficnt<<endl;
	return 0;
}
```
### 5.13
1.
```
unsigned aCnt=0,eCnt=0,iouCnt=0;
char ch=next_text();
switch(ch){
    case `a`:aCnt++;break;
    case `e`:eCnt++;break;
    default:iouCnt++;
}
```
2.
```
unsigned index=some_value();
switch(index){
    case 1:{
        int ix=get_value();
        ivec[ix]=index;
        break;
    }
    default:{
        int ix=ivec.size()-1;
        ivec[ix]=index;
    }
}
```
3.
```
unsigned evenCnt=0,oddCnt=0;
int digit=get_num()%10;
switch(digit){
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        oddCnt++;
        break;
    case 0:
    case 2:
    case 4:
    case 6:
    case 8:
        evenCnt++;
        break;
}
```
4.
```
constexpr unsigned ival=512,jval=1024,kval=4096;
unsigned bufsize;
unsigned swt=get_bufCnt();
switch(swt){
    case ival:
        bufsize=ival*sizeof(int);
        break;
    case jval:
        bufsize=jval*sizeof(int);
        break;
    case kval:
        bufsize=kval*sizeof(int);
        break;
}
```
### 5.14
```
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
	int maxcnt=1,markcnt=1;
	string maxstr,curstr,markstr;
	if(cin>>maxstr)
	{
		markstr=maxstr;
		while(cin>>curstr)
		{
			if(curstr==markstr)
			{
				++markcnt;
				if(markcnt>maxcnt)
				{
					maxcnt=markcnt;
					maxstr=markstr;
				}
			}
			else
			{
				markstr=curstr;
				markcnt=1;
			}
		}
	}
	if(maxcnt>1)
		cout<<maxstr<<" occurs "<<maxcnt<<" times."<<endl;
	else
		cout<<"no repeated words."<<endl;
	return 0;
}
```
### 5.15
1.
原文中ix超出其作用域，在if语句中是无效的变量
```
int ix=0;
for(;ix!=sz;++ix){/*......*/}
if(ix!=sz)
    //...
```
2.
原文中，for循环缺少初始化部分。
```
for(int ix=0;ix!=sz;++ix){/*......*/}
```
3.
ix与sz同时自增，无法跳出循环
```
for(int ix=0;ix!=sz;++ix){/*......*/}
```
### 5.16
待完善
### 5.17
```
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	bool flag(true);
	vector<int> ivec1{1,2,3,4,5,6,7,8};
	vector<int> ivec2{1,3,4};
	decltype(ivec1.size()) index=0,max_length;
	max_length=ivec1.size()>ivec2.size()?ivec2.size():ivec1.size();
	for(;index<max_length;++index)
	{
		if(ivec1[index]!=ivec2[index])
		{
			flag=false;
			break;
		}
	}
	if(flag)
		cout<<"Yes, it's the prefix."<<endl;
	else
		cout<<"No, it's not the prefix."<<endl;
	return 0;
}
```
### 5.18
1.
读入两个整形变量并输出它们的和
```
do
{
    int v1,v2;
    cout<<"Please enter two numbers to sum:";
    if(cin>>v1>>v2)
        cout<<"Sum is: "<<v1+v2<<endl;
}
while(cin);
```
2.
条件部分使用的变量需要定义在循环体外。
```
int ival=get_response();
do
{
//...
}
while(ival);
```
3.
条件部分使用的变量需要定义在循环体外。
```
int ival=get_response();
do
{
//...
}
while(ival);
```
### 5.19
```
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string str1,str2;
	do
	{
		cout<<"Enter two string:";

		if(cin>>str1>>str2)
		{
			if(str1.size()>str2.size())
				cout<<str2<<endl;
			else
				cout<<str1<<endl;
		}
		else
			break;
	}
	while(cin);
	return 0;
}
```
### 5.20
```
#include <iostream>
#include <string>
using namespace std;
int main()
{
	bool flag(false);
	string str1,str2;
	if(cin>>str1)
	{
		while(cin>>str2)
		{
			if(str1==str2)
			{
				flag=true;
				break;
			}
			else
				str1=str2;
		}
	}
	if(flag)
		cout<<str1<<" is repeated."<<endl;
	else
		cout<<"No words repeated."<<endl;
	return 0;
}
```
### 5.21
==5-21.cpp==
```
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main()
{
	bool flag(false);
	string str1,str2;
	if(cin>>str1)
	{
		while(cin>>str2)
		{
			if(str1==str2&&isupper(str1[0]))
			{
				flag=true;
				break;
			}
			else
				str1=str2;
		}
	}
	if(flag)
		cout<<str1<<" is repeated."<<endl;
	else
		cout<<"No words repeated."<<endl;
	return 0;
}
```
==5-21-1.cpp==
```
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main()
{
	bool flag(false);
	string str1,str2;
	if(cin>>str1)
	{
		while(cin>>str2)
		{
			if(!isupper(str1[0]))
			{
				str1=str2;
				continue;
			}
			else if(str1==str2)
			{
				flag=true;
				break;
			}
			str1=str2;
		}
	}
	if(flag)
		cout<<str1<<" is repeated."<<endl;
	else
		cout<<"No words repeated."<<endl;
	return 0;
}
```
### 5.22
```
int sz;
while((sz=getsize())<=0)
    ;
```
### 5.23
```
#include <iostream>
using namespace std;
int main()
{
	int i_1,i_2;
	cout<<"Enter two integer:";
	cin>>i_1>>i_2;
	cout<<i_1/i_2<<endl;
	return 0;
}
```
### 5.24
```
#include <iostream>
using namespace std;
int main()
{
	int i_1,i_2;
		cout<<"Enter two integer:";
		cin>>i_1>>i_2;
		if(i_2==0)
			throw runtime_error("除数不能为0");
		cout<<i_1/i_2<<endl;
	return 0;
}
```
### 5.25
```
#include <iostream>
using namespace std;
int main()
{
	int i_1,i_2;
	cout<<"Enter two integer:";
	while(cin>>i_1>>i_2)
	{
		try
		{
			if(i_2==0)
				throw runtime_error("除数不能为0");
			cout<<"The result is "<<i_1/i_2<<endl;
		}
		catch(runtime_error err)
		{
			cout<<err.what()<<"\nTry again?Enter y or n:";
			char ch;
			cin>>ch;
			if(!cin||ch=='n')
				break;
		}
	}
	return 0;
}
```
