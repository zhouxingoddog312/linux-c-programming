#include <iostream>
using namespace std;
void f();
void f(int);
void f(int ,int);
void f(double,double);
int main(void)
{
	f(42);
	f(42,0);
	f(2.56,3.14);
	return 0;
}
void f()
{
	cout<<"This is function f()."<<endl;
}
void f(int)
{
	cout<<"This is function f(int)."<<endl;
}
void f(int ,int)
{
	cout<<"This is function f(int,int)."<<endl;
}
void f(double,double=3.14)
{
	cout<<"This is function f(double,double=3.14)."<<endl;
}
