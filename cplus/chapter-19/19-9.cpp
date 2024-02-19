#include <iostream>
#include <typeinfo>
#include <string>
#include "19-6/Query.h"
using std::cout;
using std::endl;
using std::string;
int main(void)
{
	int i;
	double d;
	char c;
	string str;
	Query q("hi");
	cout<<typeid(i).name()<<","<<typeid(d).name()<<","<<typeid(c).name()<<","<<typeid(str).name()<<","<<typeid(q).name()<<endl;
	return 0;
}
