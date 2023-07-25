#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
int main(void)
{
	bool flag=true;
	int targ,tmp;
	vector<int> ivec;
	cout<<"输入要判断的那个int值:";
	cin>>targ;
	cout<<"输入一系列int值创建一个int容器:";
	while(cin>>tmp)
		ivec.push_back(tmp);
	for(const int &i:ivec)
	{
		if(modulus<int>()(targ,i)!=0)
		{
			flag=false;
			break;
		}
	}
	if(flag)
		cout<<"可以被整除"<<endl;
	else
		cout<<"不能被整除"<<endl;
	return 0;
}
