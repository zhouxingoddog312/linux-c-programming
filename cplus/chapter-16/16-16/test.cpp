#include "Vec.h"
#include <string>
#include <iostream>
using std::string;
using std::cin; using std::cout; using std::endl;
using std::istream;
void print(const Vec<string> &svec)
{
    for (string *it = svec.begin(); it != svec.end(); ++it)
        cout << *it << " ";
    cout << endl;
}
Vec<string> getVec(istream &is)
{
    Vec<string> svec;
    string s;
    while (is >> s)
        svec.push_back(s);
    return svec;
}
int main()
{
    Vec<string> svec = getVec(cin);
    print(svec);
    cout << "copy " << svec.size() << endl;
    Vec<string> svec2 = svec;
    print(svec2);
    cout << "assign" << endl;
    Vec<string> svec3;
    svec3 = svec2;
    print(svec3);
    cout << "----- end -----"<<endl;
    return 0;
}
