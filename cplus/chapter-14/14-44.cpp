#include <iostream>
#include <map>
#include <functional>
#include <string>
using namespace std;
int add(int i,int j) {return i+j;}
int main(void)
{
	struct divide
	{
		int operator()(int denominator,int divisor) {return denominator/divisor;}
	};
	auto mod=[](int x,int y)->int {return x%y;};
	map<string,function<int(int,int)>> binops=
	{
		{"+",add},
		{"-",minus<int>()},
		{"*",[](int x,int y) {return x*y;}},
		{"/",divide()},
		{"%",mod}
	};
	int a,b;
	string op;
	cout<<"输入 数字 算术符号 数字:";
	cin>>a>>op>>b;
	cout<<"结果是"<<binops[op](a,b)<<endl;
	return 0;
}
