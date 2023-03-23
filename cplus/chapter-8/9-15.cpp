#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
	vector<int> iv1={1,2,3},iv2{1,2,3};
	if(iv1==iv2)
		cout<<"It's equal.";
	else
		cout<<"Not equal.";
	cout<<endl;
	return 0;
}
