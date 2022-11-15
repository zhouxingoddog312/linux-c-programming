#include <iostream>
#include <cstddef>
using std::cout;
using std::endl;
int main()
{
	int arr_1[10];
	int arr_2[10];
	for(size_t index=0;index<10;index++)
	{
		arr_1[index]=index;
		arr_2[index]=arr_1[index];
	}
	for(auto value:arr_2)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
