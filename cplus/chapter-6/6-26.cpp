#include <iostream>
#include <string>
using namespace std;
int main(int argc,char *argv[])
{
	for(size_t index=1;index!=argc;++index)
		cout<<argv[index]<<endl;
	return 0;
}
