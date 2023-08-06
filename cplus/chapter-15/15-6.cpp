#include <iostream>
#include "Quote.h"
using namespace std;
int main(void)
{
	Quote item1("1-102-333",20);
	Bulk_quote item2("1-202-222",30,2,0.2);
	print_total(cout,item1,3);
	print_total(cout,item2,3);
	return 0;
}
