#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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
bool valid(const string &str)
{
	if(str.size()==11)
		return true;
	else
		return false;
}
string format(const string &str)
{
	return str;
}
