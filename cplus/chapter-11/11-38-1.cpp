#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int main(void)
{
	unordered_map<string,size_t> word_count;
	string tmp;
	while(cin>>tmp)
		++word_count[tmp];
	for(const auto &elemt:word_count)
	{
		cout<<elemt.first<<" occurs "<<elemt.second<<(elemt.second>1?" times":" time")<<endl;
	}
	return 0;
}
