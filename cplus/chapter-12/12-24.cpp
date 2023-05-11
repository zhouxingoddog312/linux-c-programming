#include <iostream>
using namespace std;
int main(void)
{
	size_t len;
	cout<<"How many characters:";
	cin>>len;
	char *ps=new char[len+1];
	cin.ignore();
	cin.get(ps,len+1);//对于边长输入，只接收其满足字符数组长度的部分，剩余部分留待继续处理
	cout<<ps;
	delete [] ps;
	return 0;
}
