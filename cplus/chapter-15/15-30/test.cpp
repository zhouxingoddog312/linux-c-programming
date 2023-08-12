#include <iostream>
#include <vector>
#include <memory>
#include "Quote.h"
using namespace std;
int main(void)
{
	basket bsk;
	bsk.add_item(Quote("10-100-111",20));
	bsk.add_item(Bulk_quote("11-100-222",30,5,0.2));
	bsk.add_item(Bulk_quote("11-100-222",30,5,0.2));
	bsk.total_receipt(cout);
	return 0;
}
