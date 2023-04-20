#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
	vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
	for(auto p=ivec.end()-1;p!=ivec.begin()-1;--p)
		cout<<*p<<" ";
	cout<<'\n';
	return 0;
}
