#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main(void)
{
	string trans,result;
	while(cin>>trans)
	{
		for(auto c:trans)
		{
			if(!ispunct(c))
				result+=c;
		}
		cout<<result<<endl;
		result="";
	}
	return 0;
}
