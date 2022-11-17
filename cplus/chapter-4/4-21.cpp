#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> ivec{1,2,3,4,5,6,7,8,9};
	for(auto &value:ivec)
		if(value%2)
			value*=2;
	for(auto value:ivec)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
