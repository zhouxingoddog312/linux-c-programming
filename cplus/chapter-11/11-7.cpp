#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
void addfamily(map<string,vector<string>> &fmap,const string &surname)
{
	fmap[surname];
}
void addchild(map<string,vector<string>> &fmap,const string &surname,const string &child)
{
	fmap[surname].push_back(child);
}
int main(void)
{
	map<string,vector<string>> fmap;
	addfamily(fmap,"wang");
	addchild(fmap,"zhou","yi");
	addchild(fmap,"zhou","er");
	for(const auto &p1:fmap)
	{
		cout<<p1.first<<"家：";
		for(const auto &p2:p1.second)
			cout<<p2<<" ";
		cout<<endl;
	}
	return 0;
}
