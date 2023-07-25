#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
void elimDups(vector<int> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<int> &words,vector<int>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),less<int>());
	auto wc=find_if(words.begin(),words.end(),bind(greater<int>(),std::placeholders::_1,sz));
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" greater than "<<sz<<endl;
	cout<<endl;
}
int main(void)
{
	int tmp;
	vector<int> ivec;
	cout<<"Enter some integers: ";
	while(cin>>tmp)
		ivec.push_back(tmp);
	biggies(ivec,1024);
	return 0;
}
