#include <fstream>
#include <memory>
#include <typeinfo>
#include "Query.h"
using namespace std;
int main(int argc,char *argv[])
{
	Query a("bird");
	Query b("third");
	Query_base *bp=new AndQuery(a,b);
	try
	{
		dynamic_cast<AndQuery &>(*bp);
		cout<<"translate successed."<<endl;
	}
	catch(bad_cast)
	{
		cout<<"translate failed."<<endl;
	}
	return 0;
}
