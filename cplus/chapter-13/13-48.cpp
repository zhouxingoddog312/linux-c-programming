#include <iostream>
#include <vector>
#include "13-44/String.h"
using namespace std;
int main(void)
{
	vector<String> vs;
	vs.reserve(8);
	String a("a1"),b("b2"),c("c3");
	vs.push_back(a);
	vs.push_back(b);
	vs.push_back(c);
	return 0;
}
