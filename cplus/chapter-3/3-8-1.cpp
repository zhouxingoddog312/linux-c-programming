#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main(void)
{
	string str="Hello World!!!";
	decltype(str.size()) index=0;
	for(;index!=str.size();index++)
		str[index]='X';
	cout<<str<<endl;
	return 0;
}
