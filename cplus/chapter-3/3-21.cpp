#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10,42);
	vector<int> v4{10};
	vector<int> v5{10,42};
	vector<string> v6{10};
	vector<string> v7{10,"hi"};
	
	cout<<"v1";
	if(v1.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto a=v1.cbegin();a!=v1.cend();a++)
			cout<<" "<<*a;
		cout<<endl;
	}

	cout<<"v2";
	if(v2.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto b=v2.cbegin();b!=v2.cend();b++)
			cout<<" "<<*b;
		cout<<endl;
	}

	cout<<"v3";
	if(v3.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto c=v3.cbegin();c!=v3.cend();c++)
			cout<<" "<<*c;
		cout<<endl;
	}	
	
	cout<<"v4";
	if(v4.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto d=v4.cbegin();d!=v4.cend();d++)
			cout<<" "<<*d;
		cout<<endl;
	}
	cout<<"v5";
	if(v5.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto e=v5.cbegin();e!=v5.cend();e++)
			cout<<" "<<*e;
		cout<<endl;
	}
	cout<<"v6";
	if(v6.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto f=v6.cbegin();f!=v6.cend();f++)
			cout<<" "<<*f;
		cout<<endl;
	}
	cout<<"v7";
	if(v7.empty())
		cout<<" is empty."<<endl;
	else
	{
		for(auto g=v7.cbegin();g!=v7.cend();g++)
			cout<<" "<<*g;
		cout<<endl;
	}

	return 0;
}
