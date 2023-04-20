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
bool check_sz(const string &s,string::size_type sz)
{
	return s.size()<sz;
}
string make_plural(size_t count,const string &word,const string &end)
{
	return (count>1)?(word+end):word;
}
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &s1,const string &s2)-> bool {return s1.size()<s2.size();});
	auto wc=partition(words.begin(),words.end(),bind(check_sz,_1,sz));
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" of length "<<sz<<" or longer "<<endl;
	for_each(wc,words.end(),[](const string &s){cout<<s<<" ";});
	cout<<endl;
}
int main(void)
{
	string tmp;
	vector<string> svec;
	cout<<"Enter some strings: ";
	while(cin>>tmp)
		svec.push_back(tmp);
	biggies(svec,3);
	return 0;
}
