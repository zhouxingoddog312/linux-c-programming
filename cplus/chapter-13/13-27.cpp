class HasPtr
{
	public:
		HasPtr(const std::string &s=std::string()):pts(new std::string(s)),value(0),use(new std::size_t(1)) {}
		HasPtr(const HasPtr &org):pts(org.pts),value(org.value),use(org.use) {++*use;}
		HasPtr & operator=(const HasPtr &rhs);
		~HasPtr();
	private:
		std::string *pts;
		int value;
		std::size_t *use;
};
HasPtr & HasPtr::operator=(const HasPtr &rhs)
{
	++*rhs.use;
	if(--*use==0)
	{
		delete pts;
		delete use;
	}
	pts=rhs.pts;
	value=rhs.value;
	use=rhs.use;
	return *this;
}
HasPtr::~HasPtr()
{
	if(--*use)
	{
		delete pts;
		delete use;
	}
}
