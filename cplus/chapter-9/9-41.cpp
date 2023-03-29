#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(void)
{
	vector<char> cvec{'H','e','l','l','o',' ','W','o','r','l','d'};
	string s(cvec.data(),cvec.size());
	cout<<s<<endl;
	return 0;
}
