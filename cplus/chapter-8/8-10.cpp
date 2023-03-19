#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
int main(int argc,char *argv[])
{
	string tmp;
	vector<string> svec;
	ifstream ifst(argv[1]);
	while(getline(ifst,tmp))
		svec.push_back(tmp);
	for(auto element:svec)
	{
		istringstream isstm(element);
		while(isstm>>tmp)
			cout<<tmp<<endl;
	}
	return 0;
}
