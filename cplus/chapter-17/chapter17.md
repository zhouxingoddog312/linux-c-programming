[toc]

### 17.1
`tuple<int,int,int> it(10,20,30)`
### 17.2
`tuple<string,vector<string>,pair<string,int>> someval("hello",{"hi","hello"},{"hi",10})`
### 17.3
==TextQuery.h==
```
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
#endif
```
==TextQuery.cpp==
```
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
```
==17-3.cpp==
```
#include <iostream>
#include <fstream>
#include "TextQuery.h"
using namespace std;
void runQueries(ifstream &infile)
{
	TextQuery tq(infile);
	while(true)
	{
		cout<<"enter word to look for, or q to quit:";
		string s;
		if(!(cin>>s)||s=="q")
			break;
		print(cout,tq.query(s))<<endl;
	}
}
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	runQueries(infile);
	return 0;
}
```
使用tuple更便捷。
### 17.4
==17-4.cpp==
```
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <algorithm>
#include <numeric>
#include "Sales_data.h"
using namespace std;
typedef tuple<vector<Sales_data>::size_type,vector<Sales_data>::const_iterator,vector<Sales_data>::const_iterator> matches;
vector<matches> findBook(const vector<vector<Sales_data>> &files,const string &book)
{
	vector<matches> ret;
	for(auto it=files.cbegin();it!=files.cend();++it)
	{
		auto found=equal_range(it->cbegin(),it->cend(),book,compareIsbn);
		if(found.first!=found.second)
			ret.push_back(make_tuple(it-files.cbegin(),found.first,found.second));
	}
	return ret;
}
void reportResults(istream &in,ostream &os,vector<vector<Sales_data>> &files)
{
	string s;
	while(in>>s)
	{
		auto trans=findBook(files,s);
		if(trans.empty())
		{
			cout<<s<<" not found in any stores"<<endl;
			continue;
		}
		for(auto const &store:trans)
		{
			os<<"store "<<get<0>(store)<<" sales: "<<accumulate(get<1>(store),get<2>(store),Sales_data(s))<<endl;
		}
	}
}
int main(void)
{
	vector<vector<Sales_data>> files;
	Sales_data tmp;
	ifstream in;
	string basename="text",line;
	for(size_t index=0;index!=3;++index)
	{
		in.open(basename+to_string(index));
		vector<Sales_data> file;
		while(in>>tmp)
			file.push_back(tmp);
		in.close();
		files.push_back(file);
	}
	reportResults(cin,cout,files);
	return 0;
}
```
