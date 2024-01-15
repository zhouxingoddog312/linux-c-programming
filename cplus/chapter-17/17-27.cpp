#include <iostream>
#include <regex>
#include <string>
//我也不知道邮编可能有哪些形式
//假设有111111111和1111-11111和1111 11111和1111.11111这些形式
int main(void)
{
	std::string line,fmt="$1-$3 ";
	std::regex r("(\\d{4})([-. ])?(\\d{5})");
	while(getline(std::cin,line))
	{
		line=std::regex_replace(line,r,fmt,std::regex_constants::format_no_copy);
		if(!line.empty())
			std::cout<<line<<std::endl;
	}
	return 0;
}
