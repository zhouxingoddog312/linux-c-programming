#ifndef _DEBUGDELETE_H
#define _DEBUGDELETE_H
class DebugDelete
{
	public:
		DebugDelete(std::ostream &s=std::cerr):os(s) {}
		template <typename T> void operator()(T *p) const {os<<"deleting unique_ptr"<<std::endl;delete p;}
	private:
		std::ostream &os;
};
#endif
