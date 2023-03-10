class Example
{
public:
	static double rate;
	static constexpr int vecSize=20;
	static vector<double> vec;
};
double Example::rate=6.5;
constexpr int Example::vecSize;
vector<double> Example::vec(vecSize);
