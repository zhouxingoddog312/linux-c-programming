#include <iostream>
#include <algorithm>
#include <list>
#include <string>
using namespace std;
int main(void)
{
	list<string> slst;
	string stmp;
	cout<<"Enter some strings: ";
	while(cin>>stmp&&stmp!="quit")
		slst.push_back(stmp);
	cout<<"Which string do you want to count: ";
	cin>>stmp;
	cout<<stmp<<" occurs "<<count(slst.begin(),slst.end(),stmp)<<" times."<<endl;
	return 0;
}
