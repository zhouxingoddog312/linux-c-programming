[toc]
### 18.1
1. 此时r是一个range_error类型的局部对象
2. 此时p是exception类型的指针,指向局部对象r
如果`throw p`就会抛出一个指向局部对象的指针，那么有可能在执行catch语句之前，该局部对象已经被销毁。
### 18.2
v和in可以调用其析构函数释放资源，而p无法正确释放资源，导致内存泄漏。
### 18.3
1. 使用智能指针管理p
`unique_ptr<int []> p(new int[v.size()])`
2. 使用类来控制资源的分配
```
class ptr
{
	public:
		explicit ptr(size_t len):p(new int[len]) {}
		ptr(const ptr&)=delete;
		ptr & operator=(const ptr&)=delete;
		~ptr()
		{
			delete [] p;
		}
	private:
		int *p;
};
```
