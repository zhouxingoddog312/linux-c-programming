#include <iostream>
using namespace std;
void print(const int i)
{
	cout<<i<<endl;
}
void print(const int *beg,const int *end)
{
	while(beg!=end)
		cout<<*beg++<<endl;
}
int main(void)
{
	int i=0,j[2]={0,1};
	print(i);
	print(begin(j),end(j));
	return 0;
}
