#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
struct func1
{
	bool operator()(const string &str1,const string &str2) {return str1.size()<str2.size();}
};
class func2
{
	public:
		func2(size_t n):sz(n) {}
		bool operator()(const string &str) {return str.size()>=sz;}
	private:
		size_t sz;
};
struct func3
{
	void operator()(const string &str) {cout<<str<<" ";}
};
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
void biggies(vector<string> &words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),func1());
	auto wc=find_if(words.begin(),words.end(),func2(sz));
	auto count=words.end()-wc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" of length "<<sz<<" or longer "<<endl;
	for_each(wc,words.end(),func3());
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
