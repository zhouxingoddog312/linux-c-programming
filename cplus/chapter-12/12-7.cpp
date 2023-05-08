#include <iostream>
#include <memory>
#include <vector>
using namespace std;
shared_ptr<vector<int>> create()
{
	return make_shared<vector<int>>();
}
shared_ptr<vector<int>> scan(istream &is,shared_ptr<vector<int>> pivec)
{
	int tmp;
	while(is>>tmp)
		pivec->push_back(tmp);
	return pivec;
}
void print(shared_ptr<vector<int>> pivec)
{
	for(const auto &t:*pivec)
		cout<<t<<" ";
	cout<<endl;
}
int main(void)
{
	print(scan(cin,create()));
	return 0;
}
