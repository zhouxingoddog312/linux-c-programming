#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool suit(const string &s)
{
	string target{"bdfghijklpqty"};
	if(s.find_first_of(target)==string::npos)
		return true;
	else
		return false;
}
int main(int argc,char *argv[])
{
	string word,result;
	if(argc!=2)
	{
		cerr<<"程序+文件名"<<endl;
		return EXIT_FAILURE;
	}
	ifstream fs(argv[1]);
	if(fs)
	{
		while(fs>>word)
		{
			if(suit(word))
			{
				if(word.size()>result.size())
				{
					result=word;
				}
			}
		}
	}
	if(result.size()!=0)
		cout<<"the longest word is: "<<result<<" length: "<<result.size()<<endl;
	else
		cout<<"no word suit"<<endl;
	return 0;
}
