#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
void rf(const string &str)
{
	vector<string> vs;
	string stemp;
	ifstream ifst(str);
	if(ifst)
	{
		while(ifst>>stemp)
			vs.push_back(stemp);
		for(auto p:vs)
			cout<<p<<"#";
		cout<<endl;
	}
	else
		cout<<"open file failed."<<'\n';
}
int main(void)
{
	rf("text");
	return 0;
}
