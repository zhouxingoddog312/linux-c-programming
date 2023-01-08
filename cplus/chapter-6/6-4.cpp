#include <iostream>
using namespace std;
int fact_1(void)
{
	int val;
	cout<<"Enter a number:";
	cin>>val;
	int ret=1;
	for(int i=1;i<=val;++i)
		ret*=i;
	return ret;
}
int main()
{
	int j=fact_1();
	cout<<"The factorial is "<<j<<endl;
	return 0;
}
