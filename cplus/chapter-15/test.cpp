#include <fstream>
#include "Query.h"
using namespace std;
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	TextQuery text(infile);
	Query q=Query("fiery")&Query("bird")|Query("wind");
	print(cout,q.eval(text));
	return 0;
}
