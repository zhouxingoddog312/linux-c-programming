#include <iostream>
#include <vector>
#include "13-44/String.h"
using namespace std;
int main(void)
{
	vector<String> vs;
	vs.reserve(6);
	String a("a1"),b("b2"),c("c3");
	vs.push_back(a);
	vs.push_back(std::move(b));
	vs.push_back(std::move(c));
	vs.push_back(String("hi"));
	vs.push_back("hello");
	return 0;
}
