#include <iostream>
#include <fstream>
#include <iterator>
using namespace std;
int main(int argc,char *argv[])//三个参数第一个是输入文件，第二个输出奇数，第三个输出偶数
{
	if(argc!=4)
	{
		cerr<<"usage: ./a.out arg1 arg2 arg3\n";
		return EXIT_FAILURE;
	}
	ifstream infile(argv[1]);
	ofstream ofile1(argv[2]),ofile2(argv[3]);
	istream_iterator<int> it(infile),eof;
	ostream_iterator<int> odd(ofile1," "),even(ofile2,"\n");
	while(it!=eof)
		if(*it%2)
			odd=*it++;
		else
			even=*it++;
	return 0;
}
