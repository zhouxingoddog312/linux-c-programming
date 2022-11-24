#include <iostream>
#include <vector>
using namespace std;
int main()
{
	bool flag(true);
	vector<int> ivec1{1,2,3,4,5,6,7,8};
	vector<int> ivec2{1,3,4};
	decltype(ivec1.size()) index=0,max_length;
	max_length=ivec1.size()>ivec2.size()?ivec2.size():ivec1.size();
	for(;index<max_length;++index)
	{
		if(ivec1[index]!=ivec2[index])
		{
			flag=false;
			break;
		}
	}
	if(flag)
		cout<<"Yes, it's the prefix."<<endl;
	else
		cout<<"No, it's not the prefix."<<endl;
	return 0;
}
