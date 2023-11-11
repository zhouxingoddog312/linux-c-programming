#include <vector>
#include <string>
using std::string;
using std::vector;
#include <iostream>
using std::cout; using std::endl;

#include "Blob.h"

int main()
{
	vector<string> s={"a","an","the","you"};
	Blob<string> b1(s.begin(),s.end());
	for (BlobPtr<string> p = b1.begin(); p != b1.end(); ++p)
		cout << *p << endl;
	return 0;
}
