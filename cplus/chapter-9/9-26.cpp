#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	vector<int> ivec;
	list<int> il;
	int ia[]={0,1,1,2,3,5,8,13,21,55,89};
	for(int index=0;index<(sizeof(ia)/sizeof(*ia));index++)
	{
		ivec.push_back(ia[index]);
		il.push_back(ia[index]);
	}
	for(auto pvec=ivec.begin();pvec!=ivec.end();)
	{
		if(*pvec%2==0)
			pvec=ivec.erase(pvec);
		else
			++pvec;
	}
	for(auto plist=il.begin();plist!=il.end();)
	{
		if(*plist%2)
			plist=il.erase(plist);
		else
			++plist;
	}
	cout<<"in the vector: ";
	for(const auto &vec:ivec)
		cout<<vec<<" ";
	cout<<endl;
	cout<<"in the list: ";
	for(const auto &lst:il)
		cout<<lst<<" ";
	cout<<endl;
	return 0;
}
