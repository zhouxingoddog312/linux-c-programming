#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data
{
	std::string Bookno;
	unsigned int sold={0};
	double revenue{0.0};
};
#endif
