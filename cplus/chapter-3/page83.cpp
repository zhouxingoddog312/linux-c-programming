#include <iostream>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	string s("Hello World!!!");
	decltype(s.size()) punct_cnt(0);
	for(auto c:s)
		if(ispunct(c))
			punct_cnt++;
	cout<<punct_cnt<<" punctation characters in "<<s<<endl;
	return 0;
}
