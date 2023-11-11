#include <iostream>
#include <vector>
template <typename T> void print(T &arr)
{
	for(auto it=arr.begin();it!=arr.end();++it)
		std::cout<<*it<<" ";
	std::cout<<std::endl;
}
int main(void)
{
	std::vector<int> ivec={2,4,6,8};
	print(ivec);
	return 0;
}
