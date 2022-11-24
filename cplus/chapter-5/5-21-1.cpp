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
