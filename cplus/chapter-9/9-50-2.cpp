#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	vector<string> svec;
	string tmp;
	double sum=0;
	cout<<"Enter some float:";
	while(cin>>tmp)
	{
		svec.push_back(tmp);
	}
	for(auto &s:svec)
	{
		sum+=stod(s);
	}
	cout<<"sum is "<<sum<<endl;
	return 0;
}
