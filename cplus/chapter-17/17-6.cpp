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
