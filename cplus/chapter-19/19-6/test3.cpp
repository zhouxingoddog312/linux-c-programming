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
	if(typeid(Query_base)==typeid(*bp))
		cout<<"It's Query_base class."<<endl;
	if(typeid(AndQuery)==typeid(*bp))
		cout<<"It's AndQuery class."<<endl;
	return 0;
}
