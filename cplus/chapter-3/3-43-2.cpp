#include <iostream>
using namespace std;
int main()
{
	int ia[3][4]=
	{
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11}
	};
	size_t x,y;
	for(x=0;x<3;x++)
		for(y=0;y<4;y++)
			cout<<ia[x][y]<<" ";
	cout<<endl;
	return 0;
}
