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
