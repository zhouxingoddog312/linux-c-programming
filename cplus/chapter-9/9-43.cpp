#include <iostream>
#include <string>
using namespace std;
void rep(string &s,const string &oldVal,const string &newVal)
{
	for(auto beg=s.begin();oldVal.size()<=(s.end()-beg);)
	{
		if(string{beg,beg+oldVal.size()}==oldVal)
		{
			beg=s.erase(beg,beg+oldVal.size());
			beg=s.insert(beg,newVal.begin(),newVal.end());
			advance(beg,newVal.size());
		}
		else
			++beg;
	}
}
int main(void)
{
	string s={"I tho  thru do it!"};
	rep(s,"tho","though");
	cout<<s<<endl;
	rep(s,"thru","through");
	cout<<s<<endl;
	return 0;
}
