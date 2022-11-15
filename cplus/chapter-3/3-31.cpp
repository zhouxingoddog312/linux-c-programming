#include <iostream>
#include <cstddef>
using std::cout;
using std::endl;
int main()
{
	int arr[10];
	for(size_t index=0;index<10;index++)
		arr[index]=index;
	for(auto value:arr)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
