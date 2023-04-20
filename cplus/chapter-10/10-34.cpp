#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
	vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
	for_each(ivec.crbegin(),ivec.crend(),[](int i)->void{cout<<i<<" ";});
	cout<<'\n';
	return 0;
}
