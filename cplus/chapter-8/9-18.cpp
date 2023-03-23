#include <iostream>
#include <string>
#include <deque>
using namespace std;
int main(void)
{
	deque<string> sd;
	string str;
	while(cin>>str)
		sd.push_front(str);
	for(auto psd=sd.cbegin();psd!=sd.cend();++psd)
		cout<<*psd<<endl;
	return 0;
}
