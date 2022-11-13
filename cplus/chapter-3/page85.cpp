#include <iostream>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string s("some string");
	for(decltype(s.size())index=0;index!=s.size()&&!isspace(s[index]);index++)
		s[index]=toupper(s[index]);
	cout<<s<<endl;
	return 0;
}
