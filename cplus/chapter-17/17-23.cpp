#include <iostream>
#include <regex>
//格式为11111或者11111-1111或者111111111
int main(void)
{
	std::regex r("(\\d{5})([-])?(\\d{4})?");
	std::string line;
	while(getline(std::cin,line))
	{
		for(std::sregex_iterator it(line.begin(),line.end(),r),end_it;it!=end_it;++it)
		{
			if((*it)[3].matched)
				std::cout<<it->str(1)<<"-"<<it->str(3)<<std::endl;
			else
				std::cout<<it->str()<<std::endl;
		}
	}
	return 0;
}
