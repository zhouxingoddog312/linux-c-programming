#include <iostream>
#include <string>
using namespace std;
template <typename T> ostream &print(ostream &os,const T &t)
{
	return os<<t<<endl;
}
template <typename T,typename... Args> ostream &print(ostream &os,const T &t,const Args &... res)
{
	os<<t<<",";
	return print(os,res...);
}
int main(void)
{
	print(cout,1);
	print(cout,1,"hi");
	print(cout,1,3.14,"hi",string("hello"),7);
	return 0;
}
