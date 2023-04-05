#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;
int main(void)
{
	vector<int> ivec;
	int itmp;
	int targ=0;
	cout<<"Enter some integer: ";
	while(cin>>itmp)
		ivec.push_back(itmp);
	cout<<"Which target do you count: ";
	cin.ignore(INT_MAX,'\n');
	cin.clear();
	cin>>targ;
	itmp=0;
	itmp=count(ivec.begin(),ivec.end(),targ);
	cout<<itmp<<" targets are find."<<endl;
	return 0;
}
