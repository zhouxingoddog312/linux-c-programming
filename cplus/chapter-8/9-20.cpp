#include <iostream>
#include <list>
#include <deque>
using namespace std;
int main(void)
{
	list<int> il;
	deque<int> oddq,evenq;
	int tmp;
	while(cin>>tmp)
		il.push_back(tmp);
	for(auto pl=il.cbegin();pl!=il.cend();++pl)
	{
		if(*pl%2==0)
			evenq.push_back(*pl);
		else
			oddq.push_back(*pl);
	}
	cout<<"The odd numbers: ";
	for(auto pd1=oddq.cbegin();pd1!=oddq.cend();++pd1)
		cout<<*pd1<<" ";
	cout<<endl;
	cout<<"The even numbers: ";
	for(auto pd2=evenq.cbegin();pd2!=evenq.cend();++pd2)
		cout<<*pd2<<" ";
	cout<<endl;
	return 0;
}
