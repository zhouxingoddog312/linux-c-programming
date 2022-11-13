#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<int> ivec;
	int tmp;
	while(cin>>tmp)
		ivec.push_back(tmp);
	for(decltype(ivec.size())index=0;index<ivec.size()-1;index+=2)
		cout<<ivec[index]+ivec[index+1]<<endl;
	return 0;
}
