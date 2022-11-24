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
		if(grade<60)
			gradelevel=svec[0];
		else
			gradelevel=svec[(grade-50)/10];
		if(grade!=100)
		{
			if(grade%10>7)
				gradelevel+="+";
			else if(grade%10<4)
				gradelevel+="-";
		}
		cout<<"grade is "<<gradelevel<<endl;
	}
	return 0;
}
