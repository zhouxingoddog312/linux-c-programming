#include <iostream>
#include <iterator>
using std::cout;
using std::endl;
using std::begin;
using std::end;
int main()
{
	int arr[10];
	for(int *pbeg=begin(arr),*pend=end(arr);pbeg!=pend;pbeg++)
		*pbeg=0;
	for(auto value:arr)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
