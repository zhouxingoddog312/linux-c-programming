#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <algorithm>
using namespace std;
int main(void)
{
	forward_list<int> iflst;
	list<int> ilst;
	deque<int> idq;
	vector<int> ivec{1,2,3,4,5,6,7,8,9};
	copy(ivec.begin(),ivec.end(),front_inserter(iflst));
	copy(ivec.begin(),ivec.end(),inserter(ilst,ilst.begin()));
	copy(ivec.begin(),ivec.end(),back_inserter(idq));

	for_each(iflst.begin(),iflst.end(),[](const int i)->void{cout<<i<<" ";});
	cout<<'\n';
	for_each(ilst.begin(),ilst.end(),[](const int i)->void{cout<<i<<" ";});
	cout<<'\n';
	for_each(idq.begin(),idq.end(),[](const int i)->void{cout<<i<<" ";});
	cout<<'\n';
	return 0;
}
