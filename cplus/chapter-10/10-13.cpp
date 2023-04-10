#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
bool divide(const string &s)
{
	return s.size()>=5;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	while(cin>>tmp)
		svec.push_back(tmp);
	const auto p=partition(svec.begin(),svec.end(),divide);
	for(auto beg=svec.cbegin();beg!=p;++beg)
		cout<<*beg<<" ";
	cout<<endl;
	return 0;
}
