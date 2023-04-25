#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
void addfamily(map<string,vector<pair<string,string>>> &fmap,const string &surname)
{
	fmap[surname];
}
void addchild(map<string,vector<pair<string,string>>> &fmap,const string &surname,const string &child,const string &birthday)
{
	fmap[surname].push_back({child,birthday});
}
int main(void)
{
	map<string,vector<pair<string,string>>> fmap;
	addfamily(fmap,"wang");
	addchild(fmap,"zhou","yi","1988.1.1");
	addchild(fmap,"zhou","er","1989.1.2");
	for(const auto &p1:fmap)
	{
		cout<<p1.first<<"家：";
		for(const auto &p2:p1.second)
			cout<<p2.first<<" "<<p2.second<<"	";
		cout<<endl;
	}
	return 0;
}
