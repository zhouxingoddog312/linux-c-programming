#include <iostream>
#include <memory>
#include <vector>
using namespace std;
vector<int> *create()
{
	return new vector<int>();
}
vector<int> *scan(istream &is,vector<int> *pivec)
{
	int tmp;
	while(is>>tmp)
		pivec->push_back(tmp);
	return pivec;
}
void print(vector<int> *pivec)
{
	for(const auto &t:*pivec)
		cout<<t<<" ";
	cout<<endl;
	delete pivec;
}
int main(void)
{
	print(scan(cin,create()));
	return 0;
}
