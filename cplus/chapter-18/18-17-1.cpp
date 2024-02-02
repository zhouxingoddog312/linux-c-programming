#include <iostream>	
namespace Exercise
{
	int ivar=0;
	double dvar=0;
	const int limit=1000;
}
int ivar=0;

using Exercise::ivar;
using Exercise::dvar;
using Exercise::limit;

void manip()
{

	double dvar=3.1416;
	int iobj=limit+1;
	++ivar;
	++::ivar;
}
int main(void)
{
	return 0;
}
