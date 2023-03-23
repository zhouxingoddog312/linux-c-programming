#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
	vector<int> ivec;
	cout<<ivec[0]<<endl;
	cout<<ivec.at(0)<<endl;
	cout<<ivec.front()<<endl;
	cout<<*ivec.begin()<<endl;
	return 0;
}
