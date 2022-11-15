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
	for(auto beg=ivec.begin(),end=ivec.end()-1;beg<end;beg+=1,end-=1)
		cout<<*beg+*end<<" ";
	cout<<endl;
	return 0;
}
