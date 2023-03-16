#include <iostream>
using namespace std;
istream &test(istream &is)
{
	string st;
A:	while(is.good())
	{
		is>>st;
		cout<<st<<'\n';
	}
	if(is.bad())
		cout<<"fatal error!"<<endl;
	else if(is.eof())
		cout<<"End of file."<<endl;
	else if(is.fail())
		goto A;
	is.clear();
	return is;
}
int main()
{
	test(cin);
	return 0;
}
