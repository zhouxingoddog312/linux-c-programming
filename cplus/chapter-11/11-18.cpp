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
	for(map<string,size_t>::iterator map_it=smp.begin();map_it!=smp.end();++map_it)
		cout<<map_it->first<<" occurs "<<map_it->second<<((map_it->second>1)?" times":" time")<<endl;
	return 0;
}
