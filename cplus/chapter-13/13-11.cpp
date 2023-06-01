class HasPtr
{
public:
	HasPtr(const std::string &s=std::string()):ps(new std::string(s)),i(0) {}
	HasPtr(const HasPtr &OHasPtr):ps(new std::string(*(OHasPtr.ps))),i(OHasPtr.i) {}
	HasPtr & operator=(const HasPtr &rhs) {std::string *newps=new std::string(*rhs.ps);delete ps;ps=newps;i=rhs.i;return *this;}
	~HasPtr() {delete ps;}
private:
	std::string *ps;
	int i;
}
