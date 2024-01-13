#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;
bool valid(const string &str);
string format(const string &str);
struct PersonInfo
{
	string name;
	vector<string> phones;
};
int main(int argc,char *argv[])
{
	string line,word;
	vector<PersonInfo> people;
	istringstream record;
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);
	while(getline(ifst,line))
	{
		PersonInfo info;
		record.clear(record.rdstate()&~record.failbit&~record.eofbit);
		record.str(line);
		record>>info.name;
		while(record>>word)
			info.phones.push_back(word);
		people.push_back(info);
	}
	for(const auto &pi:people)
	{
		ostringstream formatted,badnums;
		for(const auto &ph:pi.phones)
		{
			if(!valid(ph))
				badnums<<" "<<ph;
			else
				formatted<<" "<<format(ph);
		}
		if(badnums.str().empty())
			ofst<<pi.name<<" "<<formatted.str()<<endl;
		else
			cerr<<"input error: "<<pi.name<<" invalid numbers "<<badnums.str()<<endl;
	}
	return 0;
}
//假设电话号码的格式11111111111或者111-1111-1111
bool valid(const string &str)
{
	regex r("^(\\d{3})(-)?(\\d{4})(-)?(\\d{4})$");
	smatch m;
	if(regex_match(str,m,r))
	{
		return m[2].matched==m[4].matched;
	}
	return false;
}
string format(const string &str)
{
	return str;
}
