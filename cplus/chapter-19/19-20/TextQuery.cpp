#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <memory>
#include "TextQuery.h"
using namespace std;
TextQuery::TextQuery(ifstream &infile):file(new vector<string>)
{
	string text;
	while(getline(infile,text))
	{
		file->push_back(text);
		size_t line_number=file->size()-1;
		istringstream line(text);
		string word;
		while(line>>word)
		{
			shared_ptr<set<line_no>> &lines=wm[word];
			if(!lines)
				lines.reset(new set<line_no>);
			lines->insert(line_number);
		}
	}
}
TextQuery::QueryResult TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	map<string,shared_ptr<set<line_no>>>::const_iterator map_it=wm.find(sought);
	if(map_it==wm.end())
		return QueryResult(sought,nodata,file);
	else
		return QueryResult(sought,map_it->second,file);
}

std::ostream &print(std::ostream &os,const TextQuery::QueryResult &qr)
{
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<std::endl;
	for(auto num:*(qr.lines))
		os<<"\t(line "<<num+1<<")"<<*(qr.file->begin()+num)<<std::endl;
	return os;
}
