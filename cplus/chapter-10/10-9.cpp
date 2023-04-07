#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void elimDups(vector<string> &);
void pt(vector<string> &);
int main(void)
{
	string tmp;
	vector<string> svec;
	while(cin>>tmp)
		svec.push_back(tmp);
	elimDups(svec);
	return 0;
}
void elimDups(vector<string> &svec)
{
	pt(svec);
	sort(svec.begin(),svec.end());
	pt(svec);
	vector<string>::iterator end_unique=unique(svec.begin(),svec.end());
	pt(svec);
	svec.erase(end_unique,svec.end());
	pt(svec);
}
void pt(vector<string> &svec)
{
	for(const auto &s:svec)
		cout<<s<<" ";
	cout<<endl;
}
