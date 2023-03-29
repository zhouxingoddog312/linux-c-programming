#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main(void)
{
	list<int> il{1,2,3,4,5};
	vector<int> ivec{2,3,4,5,6};
	vector<double> dvec1(il.begin(),il.end());//因为容器类型不同，且元素类型不同，只能使用迭代器指定的范围初始化
	vector<double> dvec2(ivec.begin(),ivec.end());//因为元素类型不同，只能使用迭代器指定的范围初始化
	for(const auto &a:dvec1)
		cout<<a<<" ";
	cout<<endl;
	for(const auto &b:dvec2)
		cout<<b<<" ";
	cout<<endl;
	return 0;
}
