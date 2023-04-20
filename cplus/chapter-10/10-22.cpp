#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;
void elimDups(vector<string> &s)
{
	sort(s.begin(),s.end());
	auto end_unique=unique(s.begin(),s.end());
	s.erase(end_unique,s.end());
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
bool check_sz(const string &s,string::size_type sz)
{
	return s.size()>sz;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &s1,const string &s2)-> bool {return s1.size()<s2.size();});
	auto wc=find_if(words.begin(),words.end(),bind(check_sz,_1,sz));
	auto count=wc-words.begin();
	cout<<count<<" "<<make_plural(count,"word","s")<<" short than "<<sz<<endl;
	for_each(words.begin(),wc,[](const string &s){cout<<s<<" ";});
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,6);
	return 0;
}
