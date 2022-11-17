#include <iostream>
using namespace std;
int main()
{
	unsigned grade;
	string str;
	while(cin>>grade&&grade<=100)
	{
		str=(grade>90)?"high pass":(grade>75)?"pass":(grade>=60)?"low pass":"fail";
		cout<<str<<endl;
	}
	return 0;
}
