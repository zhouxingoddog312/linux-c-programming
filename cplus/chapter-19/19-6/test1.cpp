#include <fstream>
#include <memory>
#include "Query.h"
using namespace std;
int main(int argc,char *argv[])
{
	Query a("bird");
	Query b("third");
	Query_base *bp=new AndQuery(a,b);
	if(AndQuery *ap=dynamic_cast<AndQuery *>(bp))
	{
		cout<<"translate successed."<<endl;
	}
	else
		cout<<"translate failed."<<endl;
	return 0;
}
