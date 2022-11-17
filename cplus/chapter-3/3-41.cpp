#include <iostream>
#include <random>
#include <vector>
#include <iterator>
using namespace std;
int main()
{
	int arr[10];
	default_random_engine rad;
	for(size_t index=0;index<10;index++)
		arr[index]=rad()%20;
	vector<int> ivec(begin(arr),end(arr));
	for(auto value:ivec)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
