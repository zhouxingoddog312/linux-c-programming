#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
int main(void)
{
	int tmp;
	vector<int> ivec,ivec_backup;
	cout<<"Enter some integers: ";
	while(cin>>tmp)
		ivec.push_back(tmp);
	transform(ivec.begin(),ivec.end(),back_inserter(ivec_backup),bind(multiplies<int>(),std::placeholders::_1,2));
	cout<<"multiply by two:";
	for(auto i:ivec_backup)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
