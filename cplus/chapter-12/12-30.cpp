#include <iostream>
#include <fstream>
#include "12-27/TextQuery.h"
#include "12-27/QueryResult.h"
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
