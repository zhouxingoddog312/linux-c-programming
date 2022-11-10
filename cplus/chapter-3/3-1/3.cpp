#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main()
{
	int val1,val2,tmp;
	cout<<"Enter two integer:";
	cin>>val1>>val2;
	if(val1<val2)
	{
		tmp=val1;
		val1=val2;
		val2=tmp;
	}
	cout<<"Print total numbers in the range from "<<val1<<" to "<<val2<<endl;
	while(val1>=val2)
	{
		cout<<val1<<" ";
		val1--;
	}
	cout<<endl;
	return 0;
}
