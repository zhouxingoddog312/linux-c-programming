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
