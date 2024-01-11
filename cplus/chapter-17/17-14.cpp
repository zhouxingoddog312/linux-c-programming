#include <iostream>
#include <regex>
int main(void)
{
	try
	{
		std::regex r("[[:alnums:]].",std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout<<e.what()<<"\nerror code: "<<e.code()<<std::endl;
	}
	try
	{
		std::regex r("[[:alnum:]].\\",std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout<<e.what()<<"\nerror code: "<<e.code()<<std::endl;
	}
	try
	{
		std::regex r("[[:alnum:].",std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout<<e.what()<<"\nerror code: "<<e.code()<<std::endl;
	}
	try
	{
		std::regex r("[[:alnum:]]\\.(aa|aA$",std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout<<e.what()<<"\nerror code: "<<e.code()<<std::endl;
	}
	return 0;
}
