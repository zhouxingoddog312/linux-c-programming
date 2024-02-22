#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include "Sales_data.h"
using std::vector;
using std::cout;
using std::endl;
using std::function;
using std::mem_fn;
vector<Sales_data>::iterator func(const vector<Sales_data> &cSvec,double limt)
{
	function<double (const Sales_data &)> f=&Sales_data::avg_price;
	return find_if(cSvec.begin(),cSvec.end(),[&f,limt](const Sales_data &sd)->bool {return f(sd)>limt;});
}
int main(void)
{
	vector<Sales_data> svec{{"1",3,24},{"2",2,26},{"3",7,38}};
	func(svec,25);
	return 0;
}
