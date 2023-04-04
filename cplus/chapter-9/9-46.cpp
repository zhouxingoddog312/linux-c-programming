#include <iostream>
#include <string>
using namespace std;
string & name(string &s,const string &s1,const string &s2)
{
	s.insert(0,s1+" ");
	s.insert(s.size()," "+s2);
	return s;
}
int main(void)
{
	string s,s1,s2;
	cin>>s>>s1>>s2;
	name(s,s1,s2);
	cout<<s<<endl;
	return 0;
}
