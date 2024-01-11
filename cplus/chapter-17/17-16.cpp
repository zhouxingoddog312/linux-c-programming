#include <iostream>
#include <string>
#include <regex>
int main(void)
{
	std::regex r("[^c]ei");
	std::smatch result;
	std::string tmp;
	std::cout<<"Enter a word: ";
	while(std::cin>>tmp)
	{
		if(regex_match(tmp,result,r))
			std::cout<<"error word: "<<result.str()<<std::endl;
		else
			std::cout<<"right word: "<<tmp<<std::endl;
		std::cout<<"Enter a word: ";
	}
	return 0;
}
