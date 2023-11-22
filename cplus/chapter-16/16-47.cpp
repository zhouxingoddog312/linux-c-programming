#include <utility>
#include <iostream>
template <typename F,typename T1,typename T2> void flip(F f,T1 &&t1,T2 &&t2)
{
	f(std::forward<T2>(t2),std::forward<T1>(t1));
}
void print(int &i,int &j)
{
	std::cout<<"接受左值引用"<<std::endl;
}
void print(int &&i,int &&j)
{
	std::cout<<"接受右值引用"<<std::endl;
}
int main()
{
	int j=42;
	int &i=j;
	print(i,i);
	print(42,42);
	return 0;
}
