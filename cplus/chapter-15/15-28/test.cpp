#include <iostream>
#include <vector>
#include <memory>
#include "Quote.h"
using namespace std;
int main(void)
{
	/*15.28*/
	vector<Quote> Qvec;
	Qvec.push_back(Quote("10-100-111",20));
	Qvec.push_back(Bulk_quote("11-100-222",30,5,0.2));
	cout<<Qvec[0].net_price(10)+Qvec[1].net_price(10)<<endl;
	/*15.29*/
	vector<shared_ptr<Quote>> Qpvec;
	Qpvec.push_back(make_shared<Quote>("10-100-111",20));
	Qpvec.push_back(make_shared<Bulk_quote>("11-100-222",30,5,0.2));
	cout<<Qpvec[0]->net_price(10)+Qpvec[1]->net_price(10)<<endl;
	return 0;
}
