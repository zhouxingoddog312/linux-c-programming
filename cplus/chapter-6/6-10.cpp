#include <iostream>
using namespace std;
void Swap(int *p,int *q)
{
	int temp;
	temp=*p;
	*p=*q;
	*q=temp;
}
int main(void)
{
	int p=3,q=5;
	Swap(&p,&q);
	cout<<"Now,p="<<p<<" q="<<q<<endl;
	return 0;
}
