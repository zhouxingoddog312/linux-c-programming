#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<int> ivec1(10,0);
	for(decltype(ivec1.size())index=0;index!=ivec1.size();index++)
		ivec1[index]=index;
	vector<int> ivec2=ivec1;
	for(auto value:ivec2)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
