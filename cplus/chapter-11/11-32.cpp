#include <iostream>
#include <map>
#include <string>
using namespace std;
void addbook(multimap<string,string> &books,const string &author,const string &literature)
{
	books.insert(make_pair(author,literature));
}
void delbook(multimap<string,string> &books,const string &author,const string &literature)
{
	pair<multimap<string,string>::iterator,multimap<string,string>::iterator> pair_it=books.equal_range(author);
	if(pair_it.first==pair_it.second)
		cout<<"There is no author named "<<author<<endl;
	else
	{
		for(auto beg=pair_it.first,ed=pair_it.second;beg!=ed;++beg)
		{
			if(beg->second==literature)
			{
				books.erase(beg);
				cout<<"The literature "<<literature<<" writed by "<<author<<" was deleted"<<endl;
				return;
			}
		}
		cout<<"There is no book named "<<literature<<" writed by "<<author<<endl;
	}
}
void printbook(const multimap<string,string> &books)
{
	for(auto it=books.begin();it!=books.end();++it)
		cout<<"author: "<<it->first<<" literature: "<<it->second<<endl;
}
int main(void)
{
	multimap<string,string> books;
	string auth,liter;	
	cout<<"Enter author and literature(q to quit):";
	while(cin>>auth&&auth!="q")
	{
		cin>>liter;
		addbook(books,auth,liter);
	}
	cout<<"Enter author and literature to delete(q to quit):";
	while(cin>>auth&&auth!="q")
	{
		cin>>liter;
		delbook(books,auth,liter);
	}
	printbook(books);
	return 0;
}
