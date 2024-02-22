#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::placeholders::_1;
int main(void)
{
	vector<string> svec={"hi","","","hello",""};
	cout<<count_if(svec.begin(),svec.end(),bind(&string::empty,_1))<<endl;
	return 0;
}
