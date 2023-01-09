#include <iostream>
using namespace std;
int sum(initializer_list<int> il)
{
	int ret=0;
	for(auto &elem:il)
		ret+=elem;
	return ret;
}
int main()
{
	cout<<sum({1,2,3})<<endl;
	return 0;
}
