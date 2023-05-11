#include <iostream>
#include <cstring>
using namespace std;
int main(void)
{
	char str1[]="hello";
	char str2[]="world";
	size_t arrlen=strlen(str1)+strlen(str2)+2;
	char *arr=new char[arrlen];
	strcpy(arr,str1);
	strcpy(arr+strlen(str1)," ");
	strcpy(arr+strlen(arr),str2);
	cout<<arr<<endl;
	delete [] arr;
	return 0;
}
