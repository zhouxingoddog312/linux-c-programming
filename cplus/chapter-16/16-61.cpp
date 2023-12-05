#include <memory>
template <typename T,typename... Args> shared_ptr<T> Make_Shared(Args&&... rest)
{
	shared_ptr<T> res(new T(std::forward(rest)...));
	return res;
}
