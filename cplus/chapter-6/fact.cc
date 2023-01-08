#include "Chapter6.h"
int fact(int val)
{
	int ret=1;
	for(int i=1;i<=val;++i)
		ret*=i;
	return ret;
}
