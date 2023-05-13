#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
int main(int argc,char *argv[])
{
	size_t lines_number=0;
	string tmp,word;
	vector<string> text;
	map<string,set<size_t>> words_lines;
	ifstream infile(argv[1]);
	while(getline(infile,tmp))//这里如果要改成do while的模式的话，得在前面先getline，进入循环后又要判断一次读入结果，繁琐得多
	{
		text.push_back(tmp);
		istringstream ln(tmp);
		while(ln>>word)
		{
			words_lines[word].insert(lines_number);
		}
		++lines_number;
	}
	do//这里改成do while没有什么影响
	{
		cout<<"Which word do you want to find(q to quit):";
		if(!(cin>>word)||word=="q")
			break;
		const auto p=words_lines.find(word);
		if(p==words_lines.end())
			cout<<"There is no "<<word<<endl;
		else
		{
			cout<<word<<" occurs "<<(p->second).size()<<" times"<<endl;
			for(auto iter=(p->second).cbegin();iter!=(p->second).cend();++iter)
			{
				cout<<"(line "<<*iter+1<<")"<<text[*iter]<<endl;
			}
		}
	}
	while(1);
	return 0;
}
