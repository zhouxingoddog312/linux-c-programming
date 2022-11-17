#include <iostream>
using namespace std;
int main()
{
	unsigned grade;
	string str;
	while(cin>>grade&&grade<=100)
	{
		if(grade>90)
			cout<<"high pass"<<endl;
		else if(grade>75)
			cout<<"pass"<<endl;
		else if(grade>=60)
			cout<<"low pass"<<endl;
		else
			cout<<"fail"<<endl;
	}
	return 0;
}
