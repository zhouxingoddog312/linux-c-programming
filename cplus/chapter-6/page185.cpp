#include <iostream>
using namespace std;
size_t count_calls()
{
	static size_t ctr=0;
	return ++ctr;
}
int main(void)
{
	for(int i=0;i!=10;++i)
		cout<<count_calls()<<endl;
	return 0;
}
