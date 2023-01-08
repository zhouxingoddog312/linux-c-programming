#include <iostream>
using namespace std;
size_t count_calls(int )
{
	int localval=0;
	static size_t ctr=0;
	cout<<"The localval is "<<localval<<" ,but the static value is "<<ctr<<endl;
	return ++ctr;
}
int main(void)
{
	for(int i=0;i!=10;++i)
		count_calls(1);
	return 0;
}
