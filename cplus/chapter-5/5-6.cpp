#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
	vector<string> svec{"F","D","C","B","A","A++"};
	unsigned grade=0;
	string gradelevel;
	while(cin>>grade&&grade<=100)
	{
		gradelevel=grade<60?svec[0]:grade<70?svec[1]:grade<80?svec[2]:grade<90?svec[3]:grade<100?svec[4]:svec[5];
		gradelevel+=grade==100?"":grade%10>7?"+":grade%10<4?"-":"";
		cout<<"grade is "<<gradelevel<<endl;
	}
	return 0;
}
