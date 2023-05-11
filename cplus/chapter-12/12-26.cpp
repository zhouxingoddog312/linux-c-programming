#include <iostream>
#include <memory>
#include <string>
using namespace std;
int main(void)
{
	allocator<string> alloc;
	string s,*ps=alloc.allocate(5);
	string *bg=ps;
	while(cin>>s&&bg!=ps+5)
		alloc.construct(bg++,s);
	const size_t size=bg-ps;
	for(size_t i=0;i!=size;++i)
	{
		cout<<ps[i]<<endl;
		alloc.destroy(ps+i);
	}
	alloc.deallocate(ps,5);
	return 0;
}
