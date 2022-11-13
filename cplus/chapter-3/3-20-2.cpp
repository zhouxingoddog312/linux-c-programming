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
	for(decltype(ivec.size())head=0,tail=ivec.size()-1;head<tail;head+=1,tail-=1)
		cout<<ivec[head]+ivec[tail]<<endl;
	return 0;
}
