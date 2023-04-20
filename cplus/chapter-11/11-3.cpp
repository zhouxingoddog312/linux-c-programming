#include <iostream>
#include <map>
#include <string>
using namespace std;
int main(void)
{
	string tmp;
	map<string,size_t> smp;
	while(cin>>tmp)
		++smp[tmp];
	for(auto &p:smp)
		cout<<p.first<<" occurs "<<p.second<<((p.second>1)?" times":" time")<<endl;
	return 0;
}
