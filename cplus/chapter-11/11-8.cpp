#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<string>::iterator save_word(vector<string> &svec,const string &str)
{
	vector<string>::iterator svec_it=find(svec.begin(),svec.end(),str);
	if(svec_it==svec.end())
	{
		svec.push_back(str);
		return svec.end()-1;
	}
	else
		return svec_it;
}//返回值为指向插入或已存在单词的迭代器
int main(void)
{
	string tmp;
	vector<string> svec;
	while(cin>>tmp)
		save_word(svec,tmp);
	for(const auto &p:svec)
		cout<<p<<" ";
	cout<<endl;
	return 0;
}
