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
