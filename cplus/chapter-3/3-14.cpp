#include <iostream>
#include <vector>
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<int> ivec;
	int temp;
	while(cin>>temp)
	{
		ivec.push_back(temp);
	}
	return 0;
}
