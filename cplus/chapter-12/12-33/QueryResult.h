#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>
class QueryResult
{
friend std::ostream &print(std::ostream &,const QueryResult &);
public:
	QueryResult(std::string s,std::shared_ptr<std::set<std::vector<std::string>::size_type>> l,std::shared_ptr<std::vector<std::string>> f):sought(s),lines(l),file(f){}
	std::set<std::vector<std::string>::size_type>::iterator begin() const {return lines->begin();}
	std::set<std::vector<std::string>::size_type>::iterator end() const {return lines->end();}
	std::shared_ptr<std::vector<std::string>> get_file(){return file;}
private:
	std::string sought;
	std::shared_ptr<std::set<std::vector<std::string>::size_type>> lines;
	std::shared_ptr<std::vector<std::string>> file;
};
std::ostream &print(std::ostream &,const QueryResult &);
inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
{
	return (count>1)?word+ending:word;
}
#endif
