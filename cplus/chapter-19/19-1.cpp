#include <cstdlib>
#include <memory>
using std::bad_alloc;
void * operator new(size_t size)
{
	if(void *result=malloc(size))
		return result;
	else
		throw bad_alloc();
}
void operator delete(void *mem) noexcept
{
	free(mem);
}
