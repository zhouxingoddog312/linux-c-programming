#include <iostream>
#include <list>
using namespace std;
int main(void)
{
	list<int> il={0,1,2,3,4,5,6,7,8,9};
	auto bg=il.begin(),ed=il.end();
	while(bg!=ed)
	{
		if(*bg%2)
		{
			il.insert(bg,*bg);
			++bg;
		}
		else
			bg=il.erase(bg);
	}
	for(const auto &i:il)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
