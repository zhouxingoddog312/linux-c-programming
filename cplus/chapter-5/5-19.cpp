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
