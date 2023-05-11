#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main(void)
{
	string str1="hello";
	string str2="world";
	size_t arrlen=str1.size()+str2.size()+2;
	char *arr=new char[arrlen];
	str1=str1+" "+str2;
	for(size_t i=0;i!=str1.size();++i)
		arr[i]=str1[i];
	cout<<arr<<endl;
	delete [] arr;
	return 0;
}
