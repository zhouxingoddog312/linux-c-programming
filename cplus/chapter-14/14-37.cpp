#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
class func
{
	public:
		func(int tg=0):targ(tg) {}
		bool operator()(int rec) {return rec==targ;}
	private:
		int targ=0;
};
int main(void)
{
	func f(1);
	vector<int> a{0,1,2,1,3,4,5},b;
	replace_copy_if(a.begin(),a.end(),back_inserter(b),f,99);
	for(auto r:b)
		cout<<r<<endl;
	return 0;
}
