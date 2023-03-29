#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;
int main(void)
{
	list<const char *> clist={"wo","shi","shei"};
	vector<string> svec;
	svec.assign(clist.cbegin(),clist.cend());
	for(const auto &a:svec)
		cout<<a<<" ";
	cout<<endl;
	return 0;
}
