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
