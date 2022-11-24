#include <iostream>
using namespace std;
int main()
{
	int i_1,i_2;
		cout<<"Enter two integer:";
		cin>>i_1>>i_2;
		if(i_2==0)
			throw runtime_error("除数不能为0");
		cout<<i_1/i_2<<endl;
	return 0;
}
