class HasPtr
{
public:
	HasPtr(const std::string &s=std::string()):ps(new std::string(s)),i(0) {}
	HasPtr(const HasPtr &OHasPtr):ps(new std::string(*(OHasPtr.ps))),i(OHasPtr.i) {}
private:
	std::string *ps;
	int i;
}
