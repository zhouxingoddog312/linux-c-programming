#include <sstream>
#include <algorithm>
#include <cctype>
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
			std::string key_word;
			for(auto c:word)
			{
				if(!ispunct(c))
					key_word+=c;
			}
			std::shared_ptr<std::set<line_no>> &lines=wm[key_word];
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
	os<<"Executing Query for: "<<qr.sought<<std::endl;
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<std::endl;
	for(auto num:*(qr.lines))
		os<<"\t(line "<<num+1<<") "<<*(qr.file->begin()+num)<<std::endl;
	return os;
}
Query & Query::operator=(const Query &rhs)
{
	++*rhs.reference_count;
	if(--*reference_count==0)
	{
		delete q;
		delete reference_count;
	}
	q=rhs.q;
	reference_count=rhs.reference_count;
	return *this;
}
Query::~Query()
{
	if(--*reference_count==0)
	{
		delete q;
		delete reference_count;
	}
}
QueryResult NotQuery::eval(const TextQuery &text) const
{
	auto result=query.eval(text);
	auto beg=result.begin(),end=result.end();
	auto ret_lines=std::make_shared<std::set<line_no>>();
	auto sz=result.get_file()->size();
	for(std::size_t n=0;n!=sz;++n)
	{
		if(beg==end||*beg!=n)
			ret_lines->insert(n);
		else if(beg!=end)
			++beg;
	}
	return QueryResult(rep(),ret_lines,result.get_file());
}
QueryResult OrQuery::eval(const TextQuery &text) const
{
	auto left=lhs.eval(text),right=rhs.eval(text);
	auto ret_lines=std::make_shared<std::set<line_no>>(left.begin(),left.end());
	ret_lines->insert(right.begin(),right.end());
	return QueryResult(rep(),ret_lines,left.get_file());
}
QueryResult AndQuery::eval(const TextQuery &text) const
{
	auto left=lhs.eval(text),right=rhs.eval(text);
	auto ret_lines=std::make_shared<std::set<line_no>>();
	set_intersection(left.begin(),left.end(),right.begin(),right.end(),inserter(*ret_lines,ret_lines->begin()));
	return QueryResult(rep(),ret_lines,left.get_file());
}
