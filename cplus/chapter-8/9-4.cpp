#include <vector>
bool find_target(vector<int>::const_iterator beg,vector<int>::const_iterator ed,int val)
{
	while(beg!=ed)
	{
		if(*beg==val)
			return true;
		++beg;
	}
	return false;
}
