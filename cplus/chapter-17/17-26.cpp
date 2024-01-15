#include <iostream>
#include <string>
#include <vector>
#include <regex>
int main(void)
{
	std::vector<std::vector<std::string>> result;
	std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
	std::string fmt="$2.$5.$7";
	std::string line;
	while(getline(std::cin,line))
	{
		std::vector<std::string> tmp;
		for(std::sregex_iterator it(line.begin(),line.end(),r),end_it;it!=end_it;++it)
		{
			tmp.push_back(it->format(fmt));
		}
		if(!tmp.empty())
			result.push_back(tmp);
	}
	for(const auto &sv:result)
	{
		if(sv.size()==1)
			std::cout<<sv[0];
		else
		{
			for(size_t index=1;index!=sv.size();++index)
				std::cout<<sv[index]<<" ";
		}
		std::cout<<std::endl;
	}
	return 0;
}
