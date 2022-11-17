#include <iostream>
#include <vector>
#include <random>
using namespace std;
int main()
{
	default_random_engine rad;
	uniform_int_distribution<int> u(-10,10);
	size_t index;
	vector<int> ivec;
	int arr[10];
	for(index=0;index<10;index++)
		ivec.push_back(u(rad));
	cout<<"there are the vector: ";
	for(auto value:ivec)
		cout<<value<<" ";
	cout<<endl;
	for(index=0;index<10;index++)
		arr[index]=ivec[index];
	cout<<"There are the values of array: ";
	for(index=0;index<10;index++)
		cout<<arr[index]<<" ";
	cout<<endl;
	return 0;
}
