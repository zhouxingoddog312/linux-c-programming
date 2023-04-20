#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;
int main(void)
{
	istream_iterator<int> it(cin),eof;
	ostream_iterator<int> ot(cout," ");
	vector<int> ivec(it,eof);
	sort(ivec.begin(),ivec.end());
	unique_copy(ivec.begin(),ivec.end(),ot);
	return 0;
}
