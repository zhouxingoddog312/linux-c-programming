#include <iostream>
#include <map>
#include <string>
using namespace std;
void addchild(multimap<string,string> &smulmp,const string &surname,const string &child)
{
	smulmp.insert({surname,child});
}
void pt(multimap<string,string> &smulmp)
{
	for(auto it=smulmp.begin();it!=smulmp.end();++it)
		cout<<it->first<<" "<<it->second<<endl;
}
int main(void)
{
	multimap<string,string> familys;
	addchild(familys,"zhou","yi");
	addchild(familys,"wang","yi");
	addchild(familys,"zhou","er");
	pt(familys);
	return 0;
}
