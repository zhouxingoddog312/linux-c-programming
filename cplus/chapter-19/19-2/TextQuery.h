#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include "QueryResult.h"
#include "StrVec.h"
class TextQuery
{
public:
	using line_no=std::vector<std::string>::size_type;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;
private:
	std::shared_ptr<StrVec> file;
	std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
};
#endif
