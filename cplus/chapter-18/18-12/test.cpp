#include <fstream>
#include "Query.h"
using namespace std;
using chapter15::Query;
using chapter15::TextQuery;
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	TextQuery text(infile);
	Query q=Query("fiery")&Query("bird")|Query("wind");
	print(cout,q.eval(text));
	return 0;
}
