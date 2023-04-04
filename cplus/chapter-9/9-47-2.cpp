#include <iostream>
#include <string>
using namespace std;
int main(void)
{
	string s={"ab2c3d7R4E6"};
	string numbers="0123456789",alphabets="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	cout<<"The numbers: ";
	for(string::size_type pos=0;(pos=s.find_first_not_of(alphabets,pos))!=string::npos;++pos)
		cout<<s[pos]<<" ";
	cout<<endl;
	cout<<"The alphabets: ";
	for(string::size_type pos=0;(pos=s.find_first_not_of(numbers,pos))!=string::npos;++pos)
		cout<<s[pos]<<" ";
	cout<<endl;
	return 0;
}
