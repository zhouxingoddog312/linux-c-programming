#include <iostream>
using namespace std;
int main()
{
	int i_1,i_2;
	cout<<"Enter two integer:";
	while(cin>>i_1>>i_2)
	{
		try
		{
			if(i_2==0)
				throw runtime_error("除数不能为0");
			cout<<"The result is "<<i_1/i_2<<endl;
		}
		catch(runtime_error err)
		{
			cout<<err.what()<<"\nTry again?Enter y or n:";
			char ch;
			cin>>ch;
			if(!cin||ch=='n')
				break;
		}
	}
	return 0;
}
