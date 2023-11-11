#include <iostream>
#include <vector>
template <typename T> void print(T &arr)
{
	for(typename T::size_type index=0;index!=arr.size();++index)
		std::cout<<arr[index]<<" ";
	std::cout<<std::endl;
}
int main(void)
{
	std::vector<int> ivec={2,4,6,8};
	print(ivec);
	return 0;
}
