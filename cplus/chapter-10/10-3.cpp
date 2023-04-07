#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
int main(void)
{
	int tmp,sum=0;
	vector<int> ivec;
	cout<<"Enter some integers(q to quit): ";
	while(cin>>tmp)
		ivec.push_back(tmp);
	sum=accumulate(ivec.cbegin(),ivec.cend(),0);
	cout<<"Sum is "<<sum<<endl;
	return 0;
}
