#include <iostream>
#include <vector>
using namespace std;
int func_sum(int i,int j)
{
	return i+j;
}
int func_reduce(int i,int j)
{
	int temp=i-j;
	return (temp>=0)?temp:-temp;
}
int func_multiplicate(int i,int j)
{
	return i*j;
}
int func_division(int i,int j)
{
	return i/j;
}
int main()
{
	typedef int Func(int,int);
	vector<Func *> vF;
	vF.push_back(func_sum);
	vF.push_back(func_reduce);
	vF.push_back(func_multiplicate);
	vF.push_back(func_division);
	return 0;
}
