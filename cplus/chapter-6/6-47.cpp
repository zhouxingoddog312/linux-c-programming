#include <iostream>
#include <vector>
using namespace std;
void print(vector<int>::iterator beg,vector<int>::iterator ends)
{
#ifndef NDEBUG
	cout<<"Now, in the function "<<__func__<<" At the line "<<__LINE__<<". The size of the vector is"<<ends-beg<<endl;
#endif
	if(beg!=ends)
	{
		cout<<*beg++<<" ";
		print(beg,ends);
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
