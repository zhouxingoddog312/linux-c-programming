#include <vector>
vector<int>::iterator find_target(vector<int>::iterator beg,vector<int>::iterator ed,int val)
{
	while(beg!=ed)
	{
		if(*beg==val)
			return beg;
		++beg;
	}
	return beg;
}
