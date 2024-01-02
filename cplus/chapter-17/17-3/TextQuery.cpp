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
std::tuple<std::string,std::shared_ptr<std::set<std::vector<std::string>::size_type>>,std::shared_ptr<std::vector<std::string>>> TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	map<string,shared_ptr<set<line_no>>>::const_iterator map_it=wm.find(sought);
	if(map_it==wm.end())
		return tuple(sought,nodata,file);
	else
		return tuple(sought,map_it->second,file);
}
std::ostream &print(std::ostream &os,const std::tuple<std::string,std::shared_ptr<std::set<std::vector<std::string>::size_type>>,std::shared_ptr<std::vector<std::string>>> &tp)
{
	 os<<std::get<0>(tp)<<" occurs "<<std::get<1>(tp)->size()<<" "<<make_plural(std::get<1>(tp)->size(),"time","s")<<std::endl;
        for(auto num:*(get<1>(tp)))
                os<<"\t(line "<<num+1<<")"<<*(get<2>(tp)->begin()+num)<<std::endl;
        return os;
}
