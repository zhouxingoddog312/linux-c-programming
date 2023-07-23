#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class func
{
	public:
		func(size_t n):sz(n) {}
		bool operator()(const string &str) {return str.size()>sz;}
	private:
		size_t sz=0;
};
int main(int argc,char *argv[])
{
	string tmp;
	size_t wl1=0,wl2=0,wl10=0;
	func f1(0),f2(9),f10(10);
	ifstream  in(argv[1]);
	while(in>>tmp)
	{
		if(f1(tmp))
			++wl1;
		if(f2(tmp))
			++wl2;
		if(f10(tmp))
			++wl10;
	}
	in.close();
	cout<<"长度为1-9的单词有"<<wl1-wl2<<" 长度大于10的单词有"<<wl10<<endl;
	return 0;
}
