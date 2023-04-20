#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "Sales_item.h"
using namespace std;
int main(int argc,char *argv[])
{
	ifstream infile(argv[1]);
	istream_iterator<Sales_item> it(infile),eof;
	vector<Sales_item> Sales_vec(it,eof);
	sort(Sales_vec.begin(),Sales_vec.end(),compareIsbn);
	vector<Sales_item>::iterator bg=Sales_vec.begin(),ed;
	while(bg!=Sales_vec.end())
	{
		ed=find_if_not(bg,Sales_vec.end(),[bg](Sales_item &s)->bool{return s.isbn()==bg->isbn();});
		cout<<accumulate(bg,ed,Sales_item(bg->isbn()))<<endl;
		bg=ed;
	}
	return 0;
}
