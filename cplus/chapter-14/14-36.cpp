#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
struct func
{
	std::string operator()()
	{
		std::string tmp;
		getline(std::cin,tmp);
		return tmp;
	}
};
int main(void)
{
	vector<string> svec;
	func f;
	while(cin)
		svec.push_back(f());
	for(const auto a:svec)
		cout<<a<<endl;
	return 0;
}
