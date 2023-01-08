#include <iostream>
using namespace std;
unsigned absolute(int val)
{
	return val>=0?val:-val;
}
int main(void)
{
	int val;
	cout<<"Enter a integer:";
	cin>>val;
	cout<<"The absolute value of "<<val<<" is "<<absolute(val)<<endl;
	return 0;
}
