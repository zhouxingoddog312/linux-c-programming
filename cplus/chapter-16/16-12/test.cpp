#include <string>
using std::string;

#include <iostream>
using std::cout; using std::endl;

#include "Blob.h"

int main()
{
    Blob<string> b1;
    cout << b1.size() << endl;
    {
        Blob<string> b2={"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        cout << b1.size() << " " << b2.size() << endl;
    	for (BlobPtr<string> p = b2.begin(); p != b2.end(); ++p)
    	    cout << *p << endl;
    }
    cout << b1.size() << endl;
    for (BlobPtr<string> p = b1.begin(); p != b1.end(); ++p)
        cout << *p << endl;

    return 0;
}
