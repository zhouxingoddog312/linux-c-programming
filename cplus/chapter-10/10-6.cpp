#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
int main()
{
	vector<int> ivec(10,10);
	fill_n(ivec.begin(),ivec.size(),0);
	for(const auto &pi:ivec)
		cout<<pi<<" ";
	cout<<endl;
	return 0;
}
