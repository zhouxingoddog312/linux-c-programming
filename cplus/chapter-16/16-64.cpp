#include <iostream>
#include <vector>
#include <cstring>
using std::vector;
using std::string;
using std::cout;
using std::endl;
template <typename T> size_t statistic(const std::vector<T> &vec,const T &target)
{
	size_t result=0;
	for(auto member:vec)
		if(target==member)
			++result;
	return result;
}
template <> size_t statistic(const std::vector<const char *> &vec,const char * const &target)
{
	size_t result=0;
	for(auto member:vec)
		if(strcmp(member,target)==0)
			++result;
	return result;
}
int main(void)
{
	vector<const char *> svec{"ni","hi","hi","hello","hi"};
	const char *s="hi";
	cout<<"svec里有"<<statistic(svec,s)<<"个hi"<<endl;
	return 0;
}
