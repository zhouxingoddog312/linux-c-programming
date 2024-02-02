#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <tuple>
namespace chapter10
{
	class TextQuery
	{
	public:
		using line_no=std::vector<std::string>::size_type;
		TextQuery(std::ifstream &);
		std::tuple<std::string,std::shared_ptr<std::set<std::vector<std::string>::size_type>>,std::shared_ptr<std::vector<std::string>>> query(const std::string &) const;
	private:
		std::shared_ptr<std::vector<std::string>> file;
		std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;
	};
	inline std::string make_plural(std::size_t count,const std::string &word,const std::string &ending)
	{
	        return (count>1)?word+ending:word;
	}
	std::ostream &print(std::ostream &,const std::tuple<std::string,std::shared_ptr<std::set<std::vector<std::string>::size_type>>,std::shared_ptr<std::vector<std::string>>> &);
}
#endif
