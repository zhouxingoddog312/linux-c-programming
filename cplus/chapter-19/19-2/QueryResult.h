#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include "StrVec.h"
class QueryResult
{
friend std::ostream &print(std::ostream &,const QueryResult &);
public:
	QueryResult(std::string s,std::shared_ptr<std::set<std::vector<std::string>::size_type>> l,std::shared_ptr<StrVec> f):sought(s),lines(l),file(f){}
private:
	std::string sought;
	std::shared_ptr<std::set<std::vector<std::string>::size_type>> lines;
	std::shared_ptr<StrVec> file;
};
std::ostream &print(std::ostream &,const QueryResult &);
inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
{
	return (count>1)?word+ending:word;
}
#endif
