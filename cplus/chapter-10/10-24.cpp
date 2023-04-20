#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;
bool check_sz(const string &s,string::size_type sz)
{
	return s.size()>sz;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some string(q to quit):";
	while(cin>>tmp&&tmp!="q")
		svec.push_back(tmp);
	cout<<"Which string longer than:";
	cin>>tmp;
	auto p=find_if(svec.begin(),svec.end(),bind(check_sz,_1,tmp.size()));
	cout<<"The first longer than "<<tmp<<" is "<<*p<<endl;
	return 0;
}
