#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <random>
#include <vector>
#include <ctime>
using namespace std;
std::default_random_engine e(time(0));
std::uniform_int_distribution<unsigned> d;
map<string,vector<string>> buildMap(ifstream &map_file)
{
	map<string,vector<string>> trans_map;
	string key,value;
	while(map_file>>key&&getline(map_file,value))
	{
		if(value.size()>1)
			trans_map[key].push_back(value.substr(1));
		else
			throw runtime_error("no rule for "+key);
	}
	return trans_map;
}
const string & transform(const string &str,map<string,vector<string>> &m)
{
	auto map_it=m.find(str);
	if(map_it==m.end())
		return str;
	else
	{
		return map_it->second[d(e)%(map_it->second.size())];
	}
}
void word_transform(ifstream &map_file,ifstream &input)
{
	auto trans_map=buildMap(map_file);
	string text;
	while(getline(input,text))
	{
		istringstream stream(text);
		string word;
		bool firstword=true;
		while(stream>>word)
		{
			if(firstword)
				firstword=false;
			else
				cout<<" ";
			cout<<transform(word,trans_map);
		}
		cout<<endl;
	}
}
int main(int argc,char *argv[])//第一个参数是map文件，第二个参数是源文本文件
{
	ifstream map_file(argv[1]);
	ifstream input(argv[2]);
	word_transform(map_file,input);
	return 0;
}
