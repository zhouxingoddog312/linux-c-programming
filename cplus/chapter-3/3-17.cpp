#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<string> svec;
	string tmp;
	while(cin>>tmp)
		svec.push_back(tmp);
	for(auto &a:svec)
	{
		for(auto &b:a)
			b=toupper(b);
	}
	for(auto c:svec)
		cout<<c<<endl;
	return 0;
}
