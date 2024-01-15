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
#include <vector>
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
### 17.5
```
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Sales_data.h"
using namespace std;
typedef pair<vector<Sales_data>::size_type,pair<vector<Sales_data>::const_iterator,vector<Sales_data>::const_iterator>> matches;
vector<matches> findBook(const vector<vector<Sales_data>> &files,const string &book)
{
	vector<matches> ret;
	for(auto it=files.cbegin();it!=files.cend();++it)
	{
		auto found=equal_range(it->cbegin(),it->cend(),book,compareIsbn);
		if(found.first!=found.second)
			ret.push_back(make_pair(it-files.cbegin(),found));
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
			os<<"store "<<store.first<<" sales: "<<accumulate(store.second.first,store.second.second,Sales_data(s))<<endl;
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
### 17.6
```
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Sales_data.h"
using namespace std;
struct matches
{
	vector<Sales_data>::size_type index;
	vector<Sales_data>::const_iterator bg;
	vector<Sales_data>::const_iterator ed;
};
vector<matches> findBook(const vector<vector<Sales_data>> &files,const string &book)
{
	vector<matches> ret;
	matches tmp;
	for(auto it=files.cbegin();it!=files.cend();++it)
	{
		auto found=equal_range(it->cbegin(),it->cend(),book,compareIsbn);
		if(found.first!=found.second)
		{
			tmp={it-files.cbegin(),found.first,found.second};
			ret.push_back(tmp);
		}
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
			os<<"store "<<store.index<<" sales: "<<accumulate(store.bg,store.ed,Sales_data(s))<<endl;
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
### 17.7
使用tuple版本更便捷，使用pair版本稍微复杂一点，自己定义一个类的版本更自由。
### 17.8
主要看类的默认构造函数和operator+是如何定义的，在我这里会得到错误的isbn。
### 17.9
1. 64位的位集，低位为100000，其余高位为0.
2. 32位的位集，低位为11110110100110110101，其余高位为0.
3. 如果bstr包含0或1之外的其他字符，构造函数会抛出invalid_argument的异常。否则如果bstr长于8，位集将由bstr的前八位构成，如果bstr长度小于8，那么位集的低位将由bstr构成，而高位被置为0.
### 17.10
```
#include <iostream>
#include <bitset>
int main(void)
{
	std::bitset<22> a("1000000010000100101110");
	std::cout<<a<<std::endl;
	std::bitset<22> b;
	b^=~a;
	std::cout<<b<<std::endl;
	return 0;
}
```
### 17.11
如果只记录真假的话，使用一个位即可记录一对真假，10个问题的真假测验的解答用`unsigned char`或者位字段或者bitset都可以。但是如果包含100道题的话，那么`unsigned long long`只保证至少64位，所以最好还是使用bitset或者位字段。
### 17.12
<a id="1">见此处</a>
```
#include <iostream>
#include <bitset>
using namespace std;
void check(bitset<10> &question,size_t index,bool answ)
{
	question.set(index,answ);
}
int main(void)
{
	char ch;
	bool answ;
	bitset<10> question,grade,answer("1000100101");
	for(size_t i=0;i!=question.size();++i)
	{
		cout<<"Enter the answer of question "<<i<<": ";
		cin.get(ch);
		if(ch=='1'||ch=='y'||ch=='Y')
			answ=1;
		else
			answ=0;
		check(question,i,answ);
	}
	cout<<"question is:"<<question<<endl;
	grade=~(question^answer);
	cout<<"grade is:"<<grade<<endl;
	cout<<"一共得了（分）："<<grade.count()<<endl;
	return 0;
}
```
### 17.13
[见17.12](#1)
### 17.14
```
#include <iostream>
#include <regex>
int main(void)
{
	try
	{
		std::regex r("[[:alnums:]].",std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout<<e.what()<<"\nerror code: "<<e.code()<<std::endl;
	}
	try
	{
		std::regex r("[[:alnum:]].\\",std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout<<e.what()<<"\nerror code: "<<e.code()<<std::endl;
	}
	try
	{
		std::regex r("[[:alnum:].",std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout<<e.what()<<"\nerror code: "<<e.code()<<std::endl;
	}
	try
	{
		std::regex r("[[:alnum:]]\\.(aa|aA$",std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout<<e.what()<<"\nerror code: "<<e.code()<<std::endl;
	}
	return 0;
}
```
### 17.15
```
#include <iostream>
#include <string>
#include <regex>
int main(void)
{
	std::regex r("[[:alpha:]]*[^c]ei[[:alpha:]]*");
	std::smatch result;
	std::string tmp;
	std::cout<<"Enter a word: ";
	while(std::cin>>tmp)
	{
		if(regex_match(tmp,result,r))
			std::cout<<"error word: "<<result.str()<<std::endl;
		else
			std::cout<<"right word: "<<tmp<<std::endl;
		std::cout<<"Enter a word: ";
	}
	return 0;
}
```
### 17.16
如果使用[^c]ei进行初始化，那么此模式只能匹配首字母不是c的三个字母组成的单词，其余单词都不能匹配。
```
#include <iostream>
#include <string>
#include <regex>
int main(void)
{
	std::regex r("[^c]ei");
	std::smatch result;
	std::string tmp;
	std::cout<<"Enter a word: ";
	while(std::cin>>tmp)
	{
		if(regex_match(tmp,result,r))
			std::cout<<"error word: "<<result.str()<<std::endl;
		else
			std::cout<<"right word: "<<tmp<<std::endl;
		std::cout<<"Enter a word: ";
	}
	return 0;
}
```
### 17.17
```
#include <iostream>
#include <string>
#include <regex>
int main(void)
{
	std::regex r("[[:alpha:]]*[^c]ei[[:alpha:]]*",std::regex::icase);
	std::smatch result;
	std::string tmp,str;
	std::cout<<"Enter some word(ctrl+D to quit): ";
	while(std::cin>>tmp)
	{
		tmp+=" ";
		str+=tmp;
	}
	std::cout<<"all the words wrong: ";
	for(std::sregex_iterator it(str.begin(),str.end(),r),end_it;it!=end_it;++it)
	{
		std::cout<<it->str()<<" ";
	}
	std::cout<<std::endl;
	return 0;
}
```
### 17.18
没看懂意思，如果只是单纯要排除某些指定的单词的话，在匹配之后输出之前判断一下这个单词是否是要排除的那些单词之一即可，但这并不是一个好办法。
### 17.19
首先调用`m[4].str()`如果m[4]匹配了会返回一个包含输入中匹配部分的string，如果没有匹配就会返回空string。其次,由于`||`的短路求值属性，会先行判断`m[4].matched==0`，当它为false时表示m[4]已经匹配了。
### 17.20
```
#include <iostream>
#include <regex>
bool valid(const std::smatch &m)
{
	if(m[1].matched)
		return m[3].matched&&(m[4].matched==false ||m[4].str()==" ");
	else
		return !m[3].matched && m[4].str()==m[6].str();
}
int main(void)
{
	std::string line;
	std::smatch m;
	std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
	while(getline(std::cin,line))
	{
		for(std::sregex_iterator it(line.begin(),line.end(),r),end_it;it!=end_it;++it)
		{
			if(valid(*it))
				std::cout<<"valid: "<<it->str()<<std::endl;
			else
				std::cout<<"not valid: "<<it->str()<<std::endl;
		}
	}
	return 0;
}
```
### 17.21
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;
bool valid(const string &str);
string format(const string &str);
struct PersonInfo
{
	string name;
	vector<string> phones;
};
int main(int argc,char *argv[])
{
	string line,word;
	vector<PersonInfo> people;
	istringstream record;
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);
	while(getline(ifst,line))
	{
		PersonInfo info;
		record.clear(record.rdstate()&~record.failbit&~record.eofbit);
		record.str(line);
		record>>info.name;
		while(record>>word)
			info.phones.push_back(word);
		people.push_back(info);
	}
	for(const auto &pi:people)
	{
		ostringstream formatted,badnums;
		for(const auto &ph:pi.phones)
		{
			if(!valid(ph))
				badnums<<" "<<ph;
			else
				formatted<<" "<<format(ph);
		}
		if(badnums.str().empty())
			ofst<<pi.name<<" "<<formatted.str()<<endl;
		else
			cerr<<"input error: "<<pi.name<<" invalid numbers "<<badnums.str()<<endl;
	}
	return 0;
}
//假设电话号码的格式11111111111或者111-1111-1111
bool valid(const string &str)
{
	regex r("^(\\d{3})(-)?(\\d{4})(-)?(\\d{4})$");
	smatch m;
	if(regex_match(str,m,r))
	{
		return m[2].matched==m[4].matched;
	}
	return false;
}
string format(const string &str)
{
	return str;
}
```
### 17.22
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;
bool valid(const smatch &);
string format(const string &str);
struct PersonInfo
{
	string name;
	vector<string> phones;
};
int main(int argc,char *argv[])
{
	regex r("(\\d{3})([[:space:]]*)(\\d{4})([[:space:]]*)(\\d{4})");
	string line,word;
	vector<PersonInfo> people;
	istringstream record;
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);
	while(getline(ifst,line))
	{
		PersonInfo info;
		record.clear(record.rdstate()&~record.failbit&~record.eofbit);
		record.str(line);
		record>>info.name;
		getline(record,word);
		for(sregex_iterator it(word.begin(),word.end(),r),end_it;it!=end_it;++it)
			info.phones.push_back(it->str());
		people.push_back(info);
	}
	for(const auto &pi:people)
	{
		ostringstream formatted,badnums;
		for(const auto &ph:pi.phones)
		{
				formatted<<" "<<format(ph);
		}
		if(badnums.str().empty())
			ofst<<pi.name<<" "<<formatted.str()<<endl;
		else
			cerr<<"input error: "<<pi.name<<" invalid numbers "<<badnums.str()<<endl;
	}
	return 0;
}
//假设电话号码的格式11111111111或者111 1111 1111或者111-1111-1111
string format(const string &str)
{
	return str;
}
```
### 17.23
```
#include <iostream>
#include <regex>
//格式为11111或者11111-1111或者111111111
int main(void)
{
	std::regex r("(\\d{5})([-])?(\\d{4})?");
	std::string line;
	while(getline(std::cin,line))
	{
		for(std::sregex_iterator it(line.begin(),line.end(),r),end_it;it!=end_it;++it)
		{
			if((*it)[3].matched)
				std::cout<<it->str(1)<<"-"<<it->str(3)<<std::endl;
			else
				std::cout<<it->str()<<std::endl;
		}
	}
	return 0;
}
```
### 17.24
```
#include <iostream>
#include <regex>
#include <string>
int main(void)
{
	std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
	std::string line;
	std::string fmt="$2.$5.$7 ";
	while(getline(std::cin,line))
	{
		std::cout<<regex_replace(line,r,fmt,std::regex_constants::format_no_copy)<<std::endl;
	}
	return 0;
}
```
### 17.25
```
#include <iostream>
#include <regex>
#include <string>
int main(void)
{
	std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
	std::string line;
	std::string fmt="$2.$5.$7";
	while(getline(std::cin,line))
	{
		std::cout<<regex_replace(line,r,fmt,std::regex_constants::format_no_copy|std::regex_constants::format_first_only)<<std::endl;
	}
	return 0;
}
```
### 17.26
```
#include <iostream>
#include <string>
#include <vector>
#include <regex>
int main(void)
{
	std::vector<std::vector<std::string>> result;
	std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
	std::string fmt="$2.$5.$7";
	std::string line;
	while(getline(std::cin,line))
	{
		std::vector<std::string> tmp;
		for(std::sregex_iterator it(line.begin(),line.end(),r),end_it;it!=end_it;++it)
		{
			tmp.push_back(it->format(fmt));
		}
		if(!tmp.empty())
			result.push_back(tmp);
	}
	for(const auto &sv:result)
	{
		if(sv.size()==1)
			std::cout<<sv[0];
		else
		{
			for(size_t index=1;index!=sv.size();++index)
				std::cout<<sv[index]<<" ";
		}
		std::cout<<std::endl;
	}
	return 0;
}
```
###  17.27
```
#include <iostream>
#include <regex>
#include <string>
//我也不知道邮编可能有哪些形式
//假设有111111111和1111-11111和1111 11111和1111.11111这些形式
int main(void)
{
	std::string line,fmt="$1-$3 ";
	std::regex r("(\\d{4})([-. ])?(\\d{5})");
	while(getline(std::cin,line))
	{
		line=std::regex_replace(line,r,fmt,std::regex_constants::format_no_copy);
		if(!line.empty())
			std::cout<<line<<std::endl;
	}
	return 0;
}
```
### 17.28
```
#include <iostream>
#include <random>
unsigned rad()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}
int main(void)
{
	for(size_t i=0;i<100;++i)
		std::cout<<rad()<<" ";
	std::cout<<std::endl;
	return 0;
}
```
### 17.29
```
#include <iostream>
#include <random>
#include <ctime>
unsigned rad(int sd=time(0))
{
	static std::default_random_engine e(sd);
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}
int main(void)
{
	for(size_t i=0;i<100;++i)
		std::cout<<rad()<<" ";
	std::cout<<std::endl;
	return 0;
}
```
### 17.30
```
#include <iostream>
#include <random>
#include <ctime>
unsigned rad(unsigned sd=time(0),unsigned min=0,unsigned max=9)
{
	static std::default_random_engine e(sd);
	static std::uniform_int_distribution<unsigned> u(min,max);
	return u(e);
}
int main(void)
{
	for(size_t i=0;i<100;++i)
		std::cout<<rad(1,1,10)<<" ";
	std::cout<<std::endl;
	return 0;
}
```
