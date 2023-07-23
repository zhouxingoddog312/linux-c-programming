#ifndef _PTSTRBLOBPTR_H
#define _PTSTRBLOBPTR_H
#include "StrBlob.h"
class PtStrBlobPtr
{
	public:
		PtStrBlobPtr()=default;
		PtStrBlobPtr(StrBlobPtr *p):ptbp(p) {}
		StrBlobPtr & operator*() const {return *ptbp;}
		StrBlobPtr * operator->() const {return & this->operator*();}
	private:
		StrBlobPtr * ptbp=nullptr;
};
#endif
