#include <iostream>
#include <string>
using namespace std;
template <typename T,typename... Args> void foo(const T &t,const Args &... rest)
{
	cout<<"Args: "<<sizeof...(Args)<<endl;
	cout<<"rest: "<<sizeof...(rest)<<endl;
}
int main(void)
{
	int i=0;
	double d=3.14;
	string s="how now brown cow";
	foo(i,s,42,d);
	foo(s,42,"hi");
	foo(d,s);
	foo("hi");
	foo(i,42,41,43);
	return 0;
}
