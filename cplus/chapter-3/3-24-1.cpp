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
	for(auto it=ivec.begin();it<ivec.end()-1;it+=2)
		cout<<*it+*(it+1)<<" ";
	cout<<endl;
	return 0;
}
