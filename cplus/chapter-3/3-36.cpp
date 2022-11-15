#include <iostream>
#include <vector>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::begin;
using std::end;
int main()
{
	int arr1[]={1,2,3,4,5};
	int arr2[]={0,0,0,0,0};
	vector<int> ivec1{0,0,0,0,0};
	vector<int> ivec2(5,0);
	for(size_t index=0;index<5;index++)
	{
		if(arr1[index]!=arr2[index])
			goto wrong;
	}
	cout<<"Two array are equality."<<endl;
	if(ivec1==ivec2)
		cout<<"Two vector are equality."<<endl;
	else
		cout<<"Two vector are not equality."<<endl;
	return 0;

wrong:	cout<<"Two array are not equality."<<endl;
	if(ivec1==ivec2)
		cout<<"Two vector are equality."<<endl;
	else
		cout<<"Two vector are not equality."<<endl;
	return 0;
}
