#include <iostream>
#include "Quote.h"
using namespace std;
int main(void)
{
	Quote item1("1-102-333",20);
	Bulk_quote item2("1-103-222",30,2,0.2);
	cout<<item1.debug()<<endl;
	cout<<item2.debug()<<endl;
	return 0;
}
