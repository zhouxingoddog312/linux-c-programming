#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
int main(void)
{
	list<int> ilst{3,0,2,1,5,4,0,8,0,9};
	auto p=find(ilst.crbegin(),ilst.crend(),0);
	++p;
	int count=0;
	for(auto bg=ilst.begin();bg!=p.base();++bg,++count);
	cout<<"最后一个值为零的元素在list中下标为"<<count<<"的位置上。"<<endl;
	return 0;
}
