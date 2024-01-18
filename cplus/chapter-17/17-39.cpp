#include <iostream>
#include <fstream>
int main(int argc,char *argv[])
{
	int ch=0;
	size_t cnt=0;
	std::fstream inout(argv[1],std::fstream::ate|std::fstream::in|std::fstream::out);
	if(!inout)
	{
		std::cerr<<"Unable to open the file!"<<std::endl;
		return EXIT_FAILURE;
	}
	std::fstream::pos_type end_mark=inout.tellg();
	inout.seekp(-1,std::fstream::end);
	inout<<'\n';
	inout.seekg(0,std::fstream::beg);
	while(inout&&inout.tellg()!=end_mark)
	{
		ch=inout.get();
		++cnt;
		if(ch=='\n')
		{
			auto mark=inout.tellg();
			inout.seekp(0,std::fstream::end);
			inout<<cnt;
			if(inout.tellg()!=end_mark)
				inout<<" ";
			inout.seekg(mark);
		}
	}
	inout.seekp(0,std::fstream::end);
	inout<<'\n';
	return 0;
}
