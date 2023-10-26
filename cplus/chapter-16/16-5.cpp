#include <iostream>
template <unsigned N,typename T> void print(T (&arr)[N])
{
	for(const T &elem:arr)
		std::cout<<elem<<std::endl;
}
#include <string>
using std::string;
int main(void)
{
	string a[]={"hi","hello","hei"};
	print(a);
	return 0;
}
