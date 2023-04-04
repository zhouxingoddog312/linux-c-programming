#include <iostream>
#include <string>
#include <array>
using namespace std;
class date
{
	public:
		date()=default;
		date(const std::string &s);
		void print() const;
	private:
		unsigned year=2023;
		unsigned month=4;
		unsigned day=2;
		array<string,12> months={"Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
		unsigned MonthFromStr(const string &s);
};
date::date(const std::string &s)
{
	string delimiter{" ,/"};
	string::size_type month_day_delimit_pos=s.find_first_of(delimiter);
	month=MonthFromStr(s.substr(0,month_day_delimit_pos));
	string::size_type day_year_delimit_pos=s.find_first_of(delimiter,month_day_delimit_pos+1);
	day=stoi(s.substr(month_day_delimit_pos+1,day_year_delimit_pos));
	year=stoi(s.substr(day_year_delimit_pos+1));
}
void date::print() const
{
	cout<<year<<" "<<month<<" "<<day<<endl;
}
unsigned date::MonthFromStr(const string &s)
{
	if(s.empty())
		return 0;
	if(isdigit(s[0]))
		return stoi(s);
	for(size_t i=0;i!=12;++i)
	{
		if(s.find(months[i])!=string::npos)
			return i+1;
	}
	return 0;
}
int main(void)
{
	date d;
	d.print();
	date e{"January 1,1900"};
	e.print();
	date f{"1/1/1990"};
	f.print();
	date g{"Jan 1 1900"};
	g.print();
	return 0;
}
