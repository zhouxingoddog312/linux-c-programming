#include <iostream>
#include <vector>
using namespace std;
void print(vector<int>::iterator beg,vector<int>::iterator end)
{
	if(beg!=end)
	{
		cout<<*beg++<<" ";
		print(beg,end);
	}
	else
		return;
}
int main(void)
{
	vector<int> vi={1,2,3,7,4,5,6};
	print(vi.begin(),vi.end());
	return 0;
}
