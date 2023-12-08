#include <iostream>
#include <vector>
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
int main(void)
{
	vector<int> ivec={1,2,3,3,4,5,6};
	cout<<"ivec里有"<<statistic(ivec,3)<<"个3."<<endl;
	vector<double> dvec={1.0,1.1,1.1,1.1,1.3};
	cout<<"dvec里有"<<statistic(dvec,1.1)<<"个1.1"<<endl;
	vector<string> svec{"hi","hello","hi"};
	cout<<"svec里有"<<statistic(svec,string("hi"))<<"个hi"<<endl;
	return 0;
}
