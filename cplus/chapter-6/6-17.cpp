#include <iostream>
using namespace std;
bool has_upper(const string &s)
{
	for(auto c:s)
	{
		if(isupper(c))
			return true;
	}
	return false;
}
void to_lower(string &s)
{
	for(auto &c:s)
	{
		if(isupper(c))
			c=tolower(c);
	}
}
int main()
{
	string s;
	cin>>s;
	if(has_upper(s))
	{
		cout<<"has upper"<<endl;
		to_lower(s);
		cout<<"the lower case is "<<s<<endl;
	}
	else
		cout<<"pure lower"<<endl;
	return 0;
}
