#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int main(void)
{
	list<int> ilst;
	vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
	vector<int>::reverse_iterator rbg(ivec.begin()+7),red(ivec.begin()+2);
	copy(rbg,red,back_inserter(ilst));
	for_each(ilst.begin(),ilst.end(),[](int i)->void{cout<<i<<" ";});
	cout<<endl;
	return 0;
}
