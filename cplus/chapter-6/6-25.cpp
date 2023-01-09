#include <iostream>
#include <string>
using namespace std;
int main(int argc,char *argv[])
{
	string s;
	for(size_t index=1;index!=argc;++index)
		s+=argv[index];
	cout<<s<<endl;
	return 0;
}
