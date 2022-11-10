#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string st1,st2;
	while(cin>>st1>>st2)
	{
		if(st1>st2)
			cout<<st1<<endl;
		else if(st1<st2)
			cout<<st2<<endl;
	}
	return 0;
}
