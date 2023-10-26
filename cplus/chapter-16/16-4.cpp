template <typename ITER,typename VAL> ITER find_hb(ITER beg,ITER end,const VAL &val)
{
	while(beg!=end)
	{
		if(*beg!=val)
			++beg;
		else
			break;
	}
	return beg;
}
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	vector<int> ivec{1,2,3,4,5};
	list<string> slist{"hi","hello","hei"};
	auto a=find_hb(ivec.begin(),ivec.end(),3);
	auto b=find_hb(slist.begin(),slist.end(),"hi");
	cout<<*a<<endl;
	cout<<*b<<endl;
	return 0;
}
