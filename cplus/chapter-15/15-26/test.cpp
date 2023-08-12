#include <iostream>
#include "Quote.h"
int main(void)
{
	Bulk_quote bulk("10-11-222",30,5,0.2);
	Quote qu=bulk;
	qu=bulk;
	Bulk_quote qu1=bulk;
	qu1=bulk;
	qu1=std::move(bulk);
	return 0;
}
