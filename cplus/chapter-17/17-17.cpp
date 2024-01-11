#include <iostream>
#include <string>
#include <regex>
int main(void)
{
	std::regex r("[[:alpha:]]*[^c]ei[[:alpha:]]*",std::regex::icase);
	std::smatch result;
	std::string tmp,str;
	std::cout<<"Enter some word(ctrl+D to quit): ";
	while(std::cin>>tmp)
	{
		tmp+=" ";
		str+=tmp;
	}
	std::cout<<"all the words wrong: ";
	for(std::sregex_iterator it(str.begin(),str.end(),r),end_it;it!=end_it;++it)
	{
		std::cout<<it->str()<<" ";
	}
	std::cout<<std::endl;
	return 0;
}
