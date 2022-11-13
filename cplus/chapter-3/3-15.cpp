#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<string> svec;
	string temp;
	while(cin>>temp)
	{
		svec.push_back(temp);
	}
	return 0;
}
