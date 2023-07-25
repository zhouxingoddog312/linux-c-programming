#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	auto wc=find_if(svec.begin(),svec.end(),bind(not_equal_to<string>(),std::placeholders::_1,"pooh"));
	if(wc==svec.end())
		cout<<"All are pooh."<<endl;
	else
		cout<<"Find the string not equal to pooh."<<endl;
	return 0;
}
