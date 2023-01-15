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
	int i=2,j=3;
	cout<<"sum= "<<vF[0](i,j)<<endl;
	cout<<"reduce= "<<vF[1](i,j)<<endl;
	cout<<"multiplicate= "<<vF[2](i,j)<<endl;
	cout<<"division= "<<vF[3](i,j)<<endl;
	return 0;
}
