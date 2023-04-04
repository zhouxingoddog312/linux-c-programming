#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	vector<string> svec;
	string tmp;
	int sum=0;
	cout<<"Enter some integer:";
	while(cin>>tmp)
	{
		svec.push_back(tmp);
	}
	for(auto &s:svec)
	{
		sum+=stoi(s);
	}
	cout<<"sum is "<<sum<<endl;
	return 0;
}
