#include <iostream>
#include <forward_list>
using namespace std;
int main(void)
{
	forward_list<int> ifl={0,1,2,3,4,5,6,7,8,9};
	auto prev=ifl.before_begin(),cur=ifl.begin(),ed=ifl.end();
	while(cur!=ed)
	{
		if(*cur%2)
		{
			ifl.insert_after(prev,*cur);
			prev=cur;
			++cur;
		}
		else
			cur=ifl.erase_after(prev);
	}
	for(const auto &i:ifl)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
