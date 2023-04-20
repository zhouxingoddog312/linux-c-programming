#include <iostream>
#include <list>
using namespace std;
void elimDups(list<string> &);
void pt(list<string> &);
int main(void)
{
	string tmp;
	list<string> slst;
	while(cin>>tmp)
		slst.push_back(tmp);
	elimDups(slst);
	return 0;
}
void elimDups(list<string> &slst)
{
	pt(slst);
	slst.sort();
	pt(slst);
	slst.unique();
	pt(slst);
}
void pt(list<string> &slst)
{
	for(const auto &s:slst)
		cout<<s<<" ";
	cout<<endl;
}
