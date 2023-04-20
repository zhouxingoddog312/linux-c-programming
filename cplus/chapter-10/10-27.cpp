#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int main(void)
{
	list<int> ilst;
	vector<int> ivec{9,1,9,2,2,3,3,3,4,4,4,4,5,5,5,5,5};
	sort(ivec.begin(),ivec.end(),[](const int a,const int b)->bool{return a<b;});
	unique_copy(ivec.begin(),ivec.end(),back_inserter(ilst));
	for_each(ilst.begin(),ilst.end(),[](const int i)->void{cout<<i<<" ";});
	return 0;
}
