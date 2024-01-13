#include <iostream>
#include <regex>
bool valid(const std::smatch &m)
{
	if(m[1].matched)
		return m[3].matched&&(m[4].matched==false ||m[4].str()==" ");
	else
		return !m[3].matched && m[4].str()==m[6].str();
}
int main(void)
{
	std::string line;
	std::smatch m;
	std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
	while(getline(std::cin,line))
	{
		for(std::sregex_iterator it(line.begin(),line.end(),r),end_it;it!=end_it;++it)
		{
			if(valid(*it))
				std::cout<<"valid: "<<it->str()<<std::endl;
			else
				std::cout<<"not valid: "<<it->str()<<std::endl;
		}
	}
	return 0;
}
