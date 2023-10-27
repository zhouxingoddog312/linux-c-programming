template <typename T,unsigned L> T* begin(const T (&arr)[L])
{
	return arr;
}
template <typename T,unsigned L> T* end(const T (&arr)[L])
{
	return arr+L;
}
#include <iostream>
#include <string>
using namespace std;
int main(void)
{
	string arr[]={"hi","hello","hei"};
	for(auto p=begin(arr);p!=end(arr);++p)
		cout<<*p<<endl;
	return 0;
}
