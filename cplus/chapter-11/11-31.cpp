#include <iostream>
#include <map>
#include <string>
using namespace std;
void addbook(multimap<string,string> &books,const string &literature,const string &author)
{
	books.insert({literature,author});
}
void delbook(multimap<string,string> &books,const string &literature)
{
	auto it=books.find(literature);
	if(it==books.end())
		cout<<"Can't find the book "<<literature<<endl;
	else
	{
		books.erase(it);
		cout<<"The book "<<literature<<" is removed"<<endl;
	}
}
void printbook(const multimap<string,string> &books)
{
	for(auto it=books.begin();it!=books.end();++it)
		cout<<"author: "<<it->second<<" literature: "<<it->first<<endl;
}
int main(void)
{
	string liter,auth;
	multimap<string,string> books;
	cout<<"Enter literature and author(q to quit):";
	while(cin>>liter&&liter!="q")
	{
		cin>>auth;
		addbook(books,liter,auth);
	}
	cout<<"Enter literature to delete(q to quit):";
	while(cin>>liter&&liter!="q")
		delbook(books,liter);
	printbook(books);
	return 0;
}
