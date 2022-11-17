#include <iostream>
using namespace std;
int main()
{
	int ia[3][4]=
	{
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11}
	};
	int (*p) [4],*q;
	for(p=ia;p<ia+3;p++)
		for(q=*p;q<*p+4;q++)
			cout<<*q<<" ";
	cout<<endl;
	return 0;
}
