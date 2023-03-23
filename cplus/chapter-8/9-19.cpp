#include <iostream>
#include <string>
#include <list>
using namespace std;
int main(void)
{
	list<string> sl;
	string str;
	while(cin>>str)
		sl.push_front(str);
	for(auto psl=sl.cbegin();psl!=sl.cend();++psl)
		cout<<*psl<<endl;
	return 0;
}
