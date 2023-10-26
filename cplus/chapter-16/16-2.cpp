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
int main(void)
{
	std::cout<<compare(1,0)<<std::endl;
	std::cout<<compare("hi","hello")<<std::endl;
	return 0;
}
