#include <cstring>
template <typename T> int compare(const T &v1,const T&v2)
{
	if(v1<v2)
		return -1;
	if(v2<v1)
		return 1;
	return 0;
}
template <unsigned M,unsigned N> int compare(const char (&p1)[M],const char (&p2)[N])
{
	return strcmp(p1,p2);
}
#include <iostream>
#include "./Sales_data.h"
int main(void)
{
	Sales_data s1("100-11",2,30),s2("100-12",5,20);
	std::cout<<s1<<std::endl;
	std::cout<<s2<<std::endl;
	std::cout<<compare(s1,s2)<<std::endl;
	return 0;
}
