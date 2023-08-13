#include <sstream>
#include "Query.h"
TextQuery::TextQuery(std::ifstream &infile):file(new std::vector<std::string>)
{
	std::string text;
	while(getline(infile,text))
	{
		file->push_back(text);
		std::size_t line_number=file->size()-1;
		std::istringstream line(text);
		std::string word;
		while(line>>word)
		{
			std::shared_ptr<std::set<line_no>> &lines=wm[word];
			if(!lines)
				lines.reset(new std::set<line_no>);
			lines->insert(line_number);
		}
	}
}
QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	std::map<std::string,std::shared_ptr<std::set<line_no>>>::const_iterator map_it=wm.find(sought);
	if(map_it==wm.end())
		return QueryResult(sought,nodata,file);
	else
		return QueryResult(sought,map_it->second,file);
}

std::ostream &print(std::ostream &os,const QueryResult &qr)
{
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<std::endl;
	for(auto num:*(qr.lines))
		os<<"\t(line "<<num+1<<")"<<*(qr.file->begin()+num)<<std::endl;
	return os;
}
