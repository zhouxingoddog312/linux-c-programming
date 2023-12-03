#include <iostream>
#include <typeinfo>
using namespace std;
template <typename T> void f(T t)
{
	cout<<"f(T t)"<<endl;
	cout<<"t: "<<typeid(t).name()<<endl;
}
template <typename T> void f(const T* p)
{
	cout<<"f(const T*)"<<endl;
	cout<<"p: "<<typeid(p).name()<<endl;
}
template <typename T> void g(T t)
{
	cout<<"g(T t)"<<endl;
	cout<<"t: "<<typeid(t).name()<<endl;
}
template <typename T> void g(T* p)
{
	cout<<"g(T*)"<<endl;
	cout<<"p: "<<typeid(p).name()<<endl;
}
int main(void)
{
	int i=42,*p=&i;
	const int ci=42,*p2=&ci;
	g(42);
	g(p);
	g(ci);
	g(p2);
	f(42);
	f(p);
	f(ci);
	f(p2);
	return 0;
}
