class HasPtr
{
	public:
		HasPtr(const std::string &s=std::string()):pts(new std::string(s)) {}
		HasPtr(const HasPtr &org):value(org.value),pts(new std::string(*org.pts)) {}
		HasPtr & operator=(const HasPtr &rhs) {std::string *tmp=new std::string(*rhs.pts);delete pts;pts=tmp;value=rhs.value;return *this;}
		~HasPtr() {delete pts;}
	private:
		int value=0;
		std::string *pts;
};
