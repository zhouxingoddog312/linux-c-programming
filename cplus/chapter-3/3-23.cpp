#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main(void)
{
	vector<int> ivec(10,21);
	for(auto it=ivec.begin();it!=ivec.end();it++)
	{
		(*it)*=2;
		cout<<*it<<" ";
	}
	cout<<endl;
	return 0;
}
