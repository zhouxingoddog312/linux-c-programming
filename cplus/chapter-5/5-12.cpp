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
