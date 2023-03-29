#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	list<int> il={1,2,3};
	vector<int> iv{1,2,3};
	for(auto pl=il.cbegin();pl!=il.cend();pl++)
		for(auto pv=iv.cbegin();pv!=iv.cend();pv++)
		{
			if(*pl==*pv)
				cout<<*pl<<" equal "<<*pv<<endl;
			else
				cout<<*pl<<" is not equal "<<*pv<<endl;
		}
	return 0;
}
