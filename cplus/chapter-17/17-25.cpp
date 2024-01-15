#include <iostream>
#include <regex>
#include <string>
int main(void)
{
	std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
	std::string line;
	std::string fmt="$2.$5.$7";
	while(getline(std::cin,line))
	{
		std::cout<<regex_replace(line,r,fmt,std::regex_constants::format_no_copy|std::regex_constants::format_first_only)<<std::endl;
	}
	return 0;
}
