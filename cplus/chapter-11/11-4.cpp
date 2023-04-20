#include <iostream>
#include <map>
#include <string>
#include <cctype>
using namespace std;
int main(void)
{
	string tmp;
	map<string,size_t> smp;
	while(cin>>tmp)
	{
		for(size_t index=0;index<tmp.size();)
		{
			tmp[index]=tolower(tmp[index]);
			if(ispunct(tmp[index]))
				tmp.erase(index,1);
			else
				index++;
		}
		++smp[tmp];
	}
	for(auto &p:smp)
		cout<<p.first<<" occurs "<<p.second<<((p.second>1)?" times":" time")<<endl;
	return 0;
}
