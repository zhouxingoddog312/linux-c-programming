#include <iostream>
#include <random>
#include <cmath>
int main(void)
{
	std::default_random_engine e;
	std::normal_distribution<> n(4,1.5);
	std::vector<unsigned> vals(9);
	for(size_t i=0;i!=200;++i)
	{
		unsigned v=lround(n(e));
		if(v<vals.size())
			++vals[v];
	}
	for(size_t j=0;j!=vals.size();++j)
		std::cout<<j<<": "<<std::string(vals[j],'*')<<std::endl;
	return 0;
}
