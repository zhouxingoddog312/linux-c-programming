#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;
bool valid(const smatch &);
string format(const string &str);
struct PersonInfo
{
	string name;
	vector<string> phones;
};
int main(int argc,char *argv[])
{
	regex r("(\\d{3})([[:space:]]*)(\\d{4})([[:space:]]*)(\\d{4})");
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
		getline(record,word);
		for(sregex_iterator it(word.begin(),word.end(),r),end_it;it!=end_it;++it)
			info.phones.push_back(it->str());
		people.push_back(info);
	}
	for(const auto &pi:people)
	{
		ostringstream formatted,badnums;
		for(const auto &ph:pi.phones)
		{
				formatted<<" "<<format(ph);
		}
		if(badnums.str().empty())
			ofst<<pi.name<<" "<<formatted.str()<<endl;
		else
			cerr<<"input error: "<<pi.name<<" invalid numbers "<<badnums.str()<<endl;
	}
	return 0;
}
//假设电话号码的格式11111111111或者111 1111 1111或者111-1111-1111
string format(const string &str)
{
	return str;
}
