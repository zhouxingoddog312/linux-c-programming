#include <iostream>
#include "QueryResult.h"
std::ostream &print(std::ostream &os,const QueryResult &qr)
{
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "<<make_plural(qr.lines->size(),"time","s")<<std::endl;
	auto p=qr.file.begin();
	auto index=0;
	for(auto num:*(qr.lines))
	{
		os<<"\t(line "<<num+1<<")";
		for(auto mk=num-index;mk!=0;--mk,++index)
			p.incr();
		os<<p.deref()<<std::endl;
	}
	return os;
}
