#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
using namespace std;
bool isnum(const string &s)
{
	istringstream is(s);
	double d;
	char c;
	if(!(is>>d))
		return false;
	if(is>>c)
		return false;
	return true;
}
int main(void)
{
	string stmp;
	vector<string> stmp_vec;
	int itmp;
	vector<int> itmp_vec;
	vector<pair<string,int>> pvec;
	cout<<"enter some string or int:";
	while(cin>>stmp)
	{
		if(isnum(stmp))
		{
			istringstream is(stmp);
			is>>itmp;
			itmp_vec.push_back(itmp);
		}
		else
			stmp_vec.push_back(stmp);
	}
	for(size_t index=0;index<stmp_vec.size()&&index<itmp_vec.size();++index)
	{
		pvec.push_back(pair<string,int>(stmp_vec[index],itmp_vec[index]));
	}
	for(const auto &p:pvec)
		cout<<p.first<<"	"<<p.second<<endl;
	return 0;
}
