#include <iostream>
#include <memory>
using namespace std;
int main(void)
{
	unique_ptr<int> pi(new int(42));
	unique_ptr<int> pi1(pi);
	return 0;
}
