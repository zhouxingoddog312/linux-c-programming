#include <iostream>
#include <forward_list>
using namespace std;
int main(void)
{
	forward_list<int> ifl{0,1,2,3,4,5,6,7,8,9};
	for(auto prev=ifl.before_begin(),curr=ifl.begin();curr!=ifl.end();)
	{
		if(*curr%2)
			curr=ifl.erase_after(prev);
		else
			prev=curr++;
	}
	for(const auto &p:ifl)
		cout<<p<<" ";
	cout<<endl;
	return 0;
}
