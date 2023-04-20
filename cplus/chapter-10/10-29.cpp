#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	istream_iterator<string> it(infile),eof;
	vector<string> svec(it,eof);
	for_each(svec.begin(),svec.end(),[](const string &s)->void{cout<<s<<" ";});
	cout<<endl;
	return 0;
}
